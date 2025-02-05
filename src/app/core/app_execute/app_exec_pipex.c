/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exec_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:43 by mbah              #+#    #+#             */
/*   Updated: 2025/02/05 18:19:03 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	execute_cmd(t_cmd cmd)
{
	if (access(cmd.path, X_OK) != -1)
	{
		if (execve(cmd.path, cmd.args, NULL) == -1)
			return (ERROR);
		return (OK);
	}
	return (ERROR);
}

int	duplicate_fd(int old, int new)
{
	if (dup2(old, new) == -1)
		return (ERROR);
	close_file(old);
	return (OK);
}

int	exec_pipex(t_pipex *pipex)
{
	int		i;
	pid_t	pid;
	int		fd[2];
	char	*line;

	(void)i;
	(void)line;
	pipe(fd);
	if (pipe(fd) == -1)
		exit_with_error(PIPE_ERR, pipex);
	pid = fork();
	if (pid == -1)
		exit_with_error(FORK_ERR, pipex);
	if (pid == 0)
	{
		close(fd[0]);
		duplicate_fd(fd[1], STDOUT_FILENO);
		execute_cmd(pipex->cmds[0]);
		close(fd[1]);
		exit(OK);
	}
	else
	{
		close(fd[1]);
		duplicate_fd(fd[0], STDOUT_FILENO);
		duplicate_fd(pipex->out_fd, fd[0]);
		i = 0;
		while (1)
		{
			line = 0;
		}
	}
	return (0);
}
