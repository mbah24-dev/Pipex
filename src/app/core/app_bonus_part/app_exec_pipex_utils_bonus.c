/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exec_pipex_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:57:42 by mbah              #+#    #+#             */
/*   Updated: 2025/02/08 17:49:30 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	open_file(char *path, char flag)
{
	int		fd;
	t_fds	*fds;

	fd = 0;
	if (flag == 0)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == 1)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 2)
		fd = open(path, O_RDONLY, 0777);
	if (fd == -1)
	{
		fds = malloc(sizeof(t_fds));
		fds->in = -1;
		fds->out = -1;
		exit_with_error(fds);
	}
	return (fd);
}

int	duplicate_fd(int old, int new)
{
	if (dup2(old, new) == -1)
		return (ERROR);
	close_fd(old, NULL);
	return (OK);
}
