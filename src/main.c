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

#include "pipex.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	only_spaces(const char *s)
{
	while (*s)
	{
		if (!ft_isspace(*s))
			return (0);
		s++;
	}
	return (1);
}

void	check_args(int argc, char **argv, t_fds *fds)
{
	char	*temp_join;
	int		i;
	char	**cmd;

	if (argc != 5)
		ft_putstr_fd("Please Use: ./pipex infile <cmd1> <cmd2> output", 1);
	else
	{
		i = -1;
		while (++i < 2)
		{
			cmd = ft_split(argv[i + 2], ' ');
			if (!cmd)
				exit_with_error(fds, 0);
			if (!cmd[0])
				temp_join = ft_strjoin("pipex: command not found: ", argv[i + 2]);
			else
				temp_join = ft_strjoin("pipex: command not found: ", cmd[0]);
			ft_putstr_fd(temp_join, 2);
			free_split(cmd);
			free(temp_join);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_fds	*fds;

	fds = malloc(sizeof(t_fds));
	if (!fds)
		exit(-1);
	fds->in = -1;
	fds->out = -1;
	if (argc == 5 && !only_spaces(argv[2]) && !only_spaces(argv[3]))
	{
		if (!env || !*env)
		{
			free(fds);
			ft_putstr_fd("Error: No environment variables found.", 2);
			exit(1);
		}
		exec_pipex(argv, env, fds);
	}
	else
	{
		free(fds);
		check_args(argc, argv, fds);
	}
	return (0);
}
