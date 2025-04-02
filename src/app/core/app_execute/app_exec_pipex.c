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

static void	child_process_one(char **argv, char **env, int *fd, t_fds *fds)
{
	fds->in = open(argv[1], O_RDONLY, 0777);
	if (fds->in == -1)
	{
		close_fd(fd[1], fds);
		close_fd(fd[0], fds);
		exit_with_error(fds);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fds->in, STDIN_FILENO);
	close_fd(fds->in, fds);
	close_fd(fd[1], fds);
	close_fd(fd[0], fds);
	execute_cmd(argv[2], env, fds);
}

static void	child_process_two(char **argv, char **envp, int *fd, t_fds *fds)
{
	fds->out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fds->out == -1)
	{
		close_fd(fd[1], fds);
		close_fd(fd[0], fds);
		exit_with_error(fds);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fds->out, STDOUT_FILENO);
	close_fd(fd[0], fds);
	close_fd(fd[1], fds);
	close_fd(fds->out, fds);
	execute_cmd(argv[3], envp, fds);
}

void	exec_pipex(char **argv, char **envp, t_fds *fds)
{
	int		fd[2];
	pid_t	child_pid_1;
	pid_t	child_pid_2;

	if (pipe(fd) == -1)
		exit_with_error(fds);
	child_pid_1 = fork();
	if (child_pid_1 == -1)
		exit_with_error(fds);
	if (child_pid_1 == 0)
		child_process_one(argv, envp, fd, fds);
	close_fd(fd[1], fds);
	child_pid_2 = fork();
	if (child_pid_2 == -1)
		exit_with_error(fds);
	if (child_pid_2 == 0)
		child_process_two(argv, envp, fd, fds);
	close_fd(fd[0], fds);
	waitpid(child_pid_1, NULL, 0);
	waitpid(child_pid_2, NULL, 0);
	free(fds);
}
