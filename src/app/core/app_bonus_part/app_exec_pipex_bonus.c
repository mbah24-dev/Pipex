/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exec_pipex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:13:17 by mbah              #+#    #+#             */
/*   Updated: 2025/02/06 21:26:55 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	execute_cmd(t_cmd cmd)
{
	if (access(cmd.path, X_OK) != -1)
		execve(cmd.path, cmd.args, NULL);
	return (ERROR);
}

static void	child_sub_process(t_pipex *pipex, int cmd_idx)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_with_error(PIPE_ERR, pipex);
	pid = fork();
	if (pid == -1)
		exit_with_error(FORK_ERR, pipex);
	if (pid == 0)
	{
		close_fd(fd[0]);
		if (duplicate_fd(fd[1], STDOUT_FILENO) == ERROR)
			exit_with_error(DUP2_ERR, pipex);
		execute_cmd(pipex->cmds[cmd_idx]);
	}
	else
	{
		close_fd(fd[1]);
		if (duplicate_fd(fd[0], STDIN_FILENO) == ERROR)
			exit_with_error(DUP2_ERR, pipex);
		waitpid(pid, NULL, 0);
	}
}

static void	here_doc(t_pipex *pipex, char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		exit_with_error(PIPE_ERR, pipex);
	pid = fork();
	if (pid == -1)
		exit_with_error(FORK_ERR, pipex);
	if (pid == 0)
	{
		close_fd(fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close_fd(fd[1]);
		if (duplicate_fd(fd[0], STDIN_FILENO) == ERROR)
			exit_with_error(DUP2_ERR, pipex);
		wait(NULL);
	}
}

void	exec_multiple_cmd_heredoc(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 1;
			if (argc == 5)
				exit_with_error(ARG_ERR, pipex);
			here_doc(pipex, argv[2]);
		}
		else
		{
			i = 0;
			if (duplicate_fd(pipex->in_fd, STDIN_FILENO) == ERROR)
				exit_with_error(DUP2_ERR, pipex);
		}
		while (i < argc - 2)
		{
			child_sub_process(pipex, i);
			i++;
		}
		if (duplicate_fd(pipex->out_fd, STDOUT_FILENO) == ERROR)
			exit_with_error(DUP2_ERR, pipex);
		execute_cmd(pipex->cmds[i]);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if ((argc - 1) > 4)
	{
		pipex = init_pipex(argc, argv, env);
		if (pipex)
			exec_multiple_cmd_heredoc(pipex, argc, argv);
		clean_pipex(pipex);
		return (OK);
	}
	exit_with_error(ARG_ERR, NULL);
}
