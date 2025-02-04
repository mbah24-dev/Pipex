/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:08:29 by mbah              #+#    #+#             */
/*   Updated: 2025/02/04 15:15:53 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	exit_with_error(char *err_msg)
{
	perror(err_msg);
	exit(ERROR);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if ((argc - 1) != 4)
		exit_with_error(ARG_ERR);
	return (OK);
}
