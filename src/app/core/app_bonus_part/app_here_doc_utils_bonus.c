/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_here_doc_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:28:58 by mbah              #+#    #+#             */
/*   Updated: 2025/02/17 14:30:18 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	here_doc_parent_process(int *fd, t_pipex *pipex)
{
	close_fd(fd[1]);
	if (duplicate_fd(fd[0], STDIN_FILENO) == ERROR)
		exit_with_error(DUP2_ERR, pipex);
	wait(NULL);
}