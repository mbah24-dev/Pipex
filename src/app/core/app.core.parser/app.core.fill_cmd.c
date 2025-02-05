/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.core.fill_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:47:08 by mbah              #+#    #+#             */
/*   Updated: 2025/02/05 00:38:44 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

static char	*get_env_path(char **env)
{
	char	*env_path;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	env_path = NULL;
	while (env[i])
	{
		env_path = ft_strnstr(env[i], "PATH=", 5);
		if (env_path)
			break ;
		i++;
	}
	return (env_path);
}

static char	*get_cmd_path(char *cmd_name, char **env)
{
	char	*env_path;
	char	**all_paths;
	int		i;
	char	*temp;
	char	*name_tmp;

	env_path = get_env_path(env);
	all_paths = ft_split((env_path + 5), ':');
	i = -1;
	if (!all_paths)
		return (NULL);
	while (all_paths[++i])
	{
		name_tmp = ft_strjoin("/", cmd_name);
		temp = ft_strjoin(all_paths[i], name_tmp);
		free(name_tmp);
		if (access(temp, F_OK | X_OK) == 0)
		{
			free_strs(all_paths);
			return (temp);
		}
		free(temp);
	}
	free_strs(all_paths);
	return (NULL);
}

t_cmd	*fill_cmd(char **str_cmd, char **env)
{
	t_cmd	*cmds;
	int		i;

	i = 0;
	if (!str_cmd)
		return (NULL);
	while (str_cmd[i])
		i++;
	cmds = (t_cmd *) malloc(sizeof(t_cmd) * (i + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (str_cmd[i])
	{
		cmds[i].args = ft_split(str_cmd[i], ' ');
		cmds[i].name = cmds[i].args[0];
		cmds[i].path = get_cmd_path(cmds[i].name, env);
		i++;
	}
	cmds[i].args = NULL;
	cmds[i].name = NULL;
	cmds[i].path = NULL;
	return (cmds);
}
