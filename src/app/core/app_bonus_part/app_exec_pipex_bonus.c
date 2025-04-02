/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exec_pipex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:13:17 by mbah              #+#    #+#             */
/*   Updated: 2025/02/17 14:35:18 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

static void	child_sub_process(char *argv, char **env, t_fds *fds)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_with_error(fds);
	pid = fork();
	if (pid == -1)
		exit_with_error(fds);
	if (pid == 0)
	{
		close_fd(fd[0], fds);
		close_fd(fds->out, fds);
		if (duplicate_fd(fd[1], STDOUT_FILENO) == ERROR)
			exit_with_error(fds);
		execute_cmd(argv, env, fds);
	}
	else
	{
		close_fd(fd[1], fds);
		if (duplicate_fd(fd[0], STDIN_FILENO) == ERROR)
			exit_with_error(fds);
		waitpid(pid, NULL, 0);
	}
}

static void	here_doc(char *limiter, t_fds *fds)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(fd) == -1)
		exit_with_error(fds);
	pid = fork();
	if (pid == -1)
		exit_with_error(fds);
	if (pid == 0)
	{
		close_fd(fd[0], fds);
		while (1)
		{
			line = get_next_line(0);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
		here_doc_parent_process(fd, fds);
}

void	exec_multiple_cmd_heredoc(int argc, char **argv, char **env, t_fds *fds)
{
	int	i;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		fds->out = open_file(argv[argc - 1], 0);
		fds->in = -1;
		here_doc(argv[2], fds);
	}
	else
	{
		i = 2;
		fds->in = open_file(argv[1], 2);
		fds->out = open_file(argv[argc - 1], 1);
		if (duplicate_fd(fds->in, STDIN_FILENO) == ERROR)
			exit_with_error(fds);
	}
	while (i < argc - 2)
		child_sub_process(argv[i++], env, fds);
	if (duplicate_fd(fds->out, STDOUT_FILENO) == ERROR)
		exit_with_error(fds);
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
		close_fd(fds->in, fds);
	execute_cmd(argv[argc - 2], env, fds);
}

int	main(int argc, char **argv, char **env)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (!fds)
		exit(-1);
	fds->in = -1;
	fds->out = -1;
	if ((argc - 1) >= 4)
	{
		exec_multiple_cmd_heredoc(argc, argv, env, fds);
		free(fds);
		return (OK);
	}
	{
		free(fds);
		ft_putstr_fd("Error: Bad arguments\n", 2);
	}
	return (ERROR);
}
