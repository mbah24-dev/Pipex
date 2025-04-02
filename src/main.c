/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:08:29 by mbah              #+#    #+#             */
/*   Updated: 2025/02/06 19:07:20 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (!fds)
		exit(-1);
	fds->in = -1;
	fds->out = -1;
	if (argc == 5)
		exec_pipex(argv, env, fds);
	else
	{
		free(fds);
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Please Use: ./pipex infile <cmd1> <cmd2> output\n", 1);
	}
	return (0);
}
