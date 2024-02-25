/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:58:24 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/02/24 22:13:01 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

char	*create_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static void	get_infile(char **argv, t_pipex *pipex)
{
	if (pipex->here_doc == 1)
		here_doc(argv[2], pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			msg_error(ERR_INFILE);
	}
}

static void	get_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		msg_error(ERR_OUTFILE);
}

static void	create_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			dad_free(pipex);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < check_numargc(argv[1], &pipex))
		msg_error(ERR_INPUT);
	get_infile(argv, &pipex);
	get_outfile(argv[argc - 1], &pipex);
	pipex.cmd_nmbs = argc - 3 - pipex.here_doc;
	pipex.pipe_nmbs = 2 * (pipex.cmd_nmbs - 1);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs);
	if (!pipex.pipe)
		send_error(ERR_PIPE);
	pipex.env_path = create_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	if (pipex.cmd_paths == NULL)
		send_error(ERR_CMD);
	create_pipe(&pipex);
	pipex.idx = -1;
	while (++(pipex.idx) < pipex.cmd_nmbs)
		child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	dad_free(&pipex);
	return (0);
}
