/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_parse_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:14:08 by mbah              #+#    #+#             */
/*   Updated: 2025/02/05 15:46:42 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

char	*get_infile_path(char **argv, t_pipex *pipex)
{
	char	*path;

	path = argv[1];
	if (access(path, F_OK | R_OK) == -1)
		exit_with_error(PATH_ERR, pipex);
	return (path);
}

char	*get_output_path(int argc, char **argv, t_pipex *pipex)
{
	char	*path;

	path = argv[argc - 1];
	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		exit_with_error(PATH_ERR, pipex);
	return (path);
}

char	**get_all_commands(int argc, char **argv)
{
	char	**commands;
	int		i;

	commands = (char **) malloc(sizeof(char *) * (argc - 2));
	if (!commands || !argv)
		return (NULL);
	i = 2;
	while (i < argc - 1 && argv[i])
	{
		commands[i - 2] = ft_strdup(argv[i]);
		i++;
	}
	commands[i - 2] = NULL;
	return (commands);
}
