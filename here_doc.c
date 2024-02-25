/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:54:23 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/02/24 22:12:48 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	generate_heredoc(void)
{
	int	file;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		send_error(ERR_HEREDOC);
	return (file);
}

void	here_doc(char *argv, t_pipex *pipex)
{
	int		file;
	char	*buf;

	file = generate_heredoc();
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".heredoc_tmp");
		send_error(ERR_HEREDOC);
	}
}

int	check_numargc(char *argv, t_pipex *pipex)
{
	if (argv && !ft_strncmp("here_doc", argv, 8))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}
