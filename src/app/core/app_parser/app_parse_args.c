/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_parse_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:14:08 by mbah              #+#    #+#             */
/*   Updated: 2025/02/06 18:28:03 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	close_fd(int fd, t_fds *fds)
{
	(void)fds;
	if (fd != -1)
	{
		if (close(fd) == -1)
			perror("close err");
	}
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	exit_with_error(t_fds *fds)
{
	if (fds != NULL)
	{
		if (fds->in != -1)
			close_fd(fds->in, fds);
		if (fds->out != -1)
			close_fd(fds->out, fds);
		free(fds);
	}
	perror("Error");
	exit(EXIT_FAILURE);
}

void	execute_cmd(char *argv, char **env, t_fds *fds)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], env);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit_with_error(fds);
	}
	if (execve(path, cmd, env) == -1)
	{
		exit_with_error(fds);
	}
}
