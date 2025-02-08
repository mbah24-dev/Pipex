/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:05:53 by mbah              #+#    #+#             */
/*   Updated: 2025/02/06 20:29:13 by mbah             ###   ########.fr       */
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
	free(pipex);
}
