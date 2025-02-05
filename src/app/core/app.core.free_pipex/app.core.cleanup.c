/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.core.cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:05:53 by mbah              #+#    #+#             */
/*   Updated: 2025/02/05 00:31:52 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	clean_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex)
		return ;
	if (pipex->cmds)
	{
		while (pipex->cmds[i].name)
		{
			if (pipex->cmds[i].path)
				free(pipex->cmds[i].path);
			if (pipex->cmds[i].args)
				free_strs(pipex->cmds[i].args);
			i++;
		}
		free(pipex->cmds);
	}
	close_file(pipex->in_fd);
	close_file(pipex->out_fd);
	free(pipex);
}
