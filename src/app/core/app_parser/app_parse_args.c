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

#include "pipex.h"

void	close_fd(int fd, t_fds *fds)
{
	(void)fds;
	if (fd != -1)
	{
		if (close(fd) == -1)
			return ;
	}
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = get_line_content_path(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	exit_with_error(t_fds *fds, int flag)
{
	if (fds != NULL)
	{
		if (fds->in != -1)
			close_fd(fds->in, fds);
		if (fds->out != -1)
			close_fd(fds->out, fds);
		free(fds);
	}
	if (flag)
		perror("Error");
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	execute_cmd(char *argv, char **env, t_fds *fds)
{
	char	**cmd;
	int		i;
	char	*path;
	char	*temp_join;

	i = -1;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		exit_with_error(fds, 0);
	path = find_path(cmd[0], env);
	if (!path)
	{
		temp_join = ft_strjoin("pipex: command not found: ", cmd[0]);
		ft_putstr_fd(temp_join, 2);
		ft_putstr_fd("\n", 2);
		free(temp_join);
		free_split(cmd);
		free(fds);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		exit_with_error(fds, 1);
	}
}
