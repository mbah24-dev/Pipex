/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:08:29 by mbah              #+#    #+#             */
/*   Updated: 2025/02/05 00:17:07 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	exit_with_error(char *err_msg, t_pipex *pipex)
{
	perror(err_msg);
	if (pipex)
		clean_pipex(pipex);
	exit(ERROR);
}

int	open_file(char *path, char flag, t_pipex *pipex)
{
	int	fd;

	if (flag == 1)
		fd = open(path, O_WRONLY);
	else
		fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		exit_with_error(FILE_ERR, pipex);
	return (fd);
}

void	close_file(int fd)
{
	if (close(fd) == -1)
		exit_with_error(CLOSE_ERR, NULL);
}

static t_pipex	*init_pipex(int argc, char **argv, char **env)
{
	char	**all_cmds;
	t_pipex	*pipex;

	all_cmds = get_all_commands(argc, argv);
	pipex = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex)
		exit_with_error(MALLOC_ERR, NULL);
	pipex->infile = get_infile_path(argv, pipex);
	pipex->output = get_output_path(argc, argv, pipex);
	pipex->in_fd = open_file(pipex->infile, 1, pipex);
	pipex->out_fd = open_file(pipex->output, 2, pipex);
	pipex->cmds = fill_cmd(all_cmds, env);
	free_strs(all_cmds);
	return (pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if ((argc - 1) >= 4)
	{
		pipex = init_pipex(argc, argv, env);
		clean_pipex(pipex);
		return (OK);
	}
	exit_with_error(ARG_ERR, NULL);
}
