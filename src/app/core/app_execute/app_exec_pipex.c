/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exec_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:43 by mbah              #+#    #+#             */
/*   Updated: 2025/02/06 16:48:01 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	execute_cmd(t_cmd cmd)
{
	if (access(cmd.path, X_OK) != -1)
		execve(cmd.path, cmd.args, NULL);
	return (ERROR);
}

int	duplicate_fd(int old, int new)
{
	if (dup2(old, new) == -1)
		return (ERROR);
	close_fd(old);
	return (OK);
}

void	child_process(t_pipex *pipex, int *fd, int cmd_idx)
{
	close_fd(fd[0]);
	if (duplicate_fd(fd[1], STDOUT_FILENO) == ERROR)
		exit_with_error(DUP2_ERR, pipex);
	if (duplicate_fd(pipex->in_fd, STDIN_FILENO) == ERROR)
		exit_with_error(DUP2_ERR, pipex);
	execute_cmd(pipex->cmds[cmd_idx]);
	clean_pipex(pipex);
	exit(ERROR);
}

void	parent_process(t_pipex *pipex, int *fd, int cmd_idx)
{
	close_fd(fd[1]);
	if (duplicate_fd(fd[0], STDIN_FILENO) == ERROR)
		exit_with_error(DUP2_ERR, pipex);
	if (duplicate_fd(pipex->out_fd, STDOUT_FILENO) == ERROR)
		exit_with_error(DUP2_ERR, pipex);
	execute_cmd(pipex->cmds[cmd_idx]);
}

void	exec_pipex(t_pipex *pipex)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_with_error(PIPE_ERR, pipex);
	pid = fork();
	if (pid == -1)
		exit_with_error(FORK_ERR, pipex);
	if (pid == 0)
		child_process(pipex, fd, 0);
	else
	{
		parent_process(pipex, fd, 1);
		waitpid(pid, NULL, 0);
	}
}
