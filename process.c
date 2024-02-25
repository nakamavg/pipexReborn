/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:18:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/02/24 21:33:01 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_pipex p, char **argv, char **envp)
{
	p.pid = fork();
	if (!p.pid)
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		p.cmd_args = ft_split(argv[2 + p.here_doc + p.idx], ' ');
		p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			msg_error(ERR_CMD);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}
