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

static void	child_process(char **argv, char **env, int *fd, t_fds *fds)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		exit_with_error(fds);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close_fd(fd_in, fds);
	close_fd(fd[1], fds);
	close_fd(fd[0], fds);
	execute_cmd(argv[2], env, fds);
}

static void	parent_process(char **argv, char **envp, int *fd, t_fds *fds)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		exit_with_error(fds);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_fd(fd[0], fds);
	close_fd(fd[1], fds);
	close_fd(fd_out, fds);
	execute_cmd(argv[3], envp, fds);
}

void	exec_pipex(char **argv, char **envp, t_fds *fds)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit_with_error(fds);
	pid = fork();
	if (pid == -1)
		exit_with_error(fds);
	if (pid == 0)
		child_process(argv, envp, fd, fds);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, fd, fds);
}
