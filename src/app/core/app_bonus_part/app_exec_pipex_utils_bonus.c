/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exec_pipex_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:57:42 by mbah              #+#    #+#             */
/*   Updated: 2025/02/06 21:08:57 by mbah             ###   ########.fr       */
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

	fd = 0;
	if (flag == 0)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == 1)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 2)
		fd = open(path, O_RDONLY, 0777);
	if (fd == -1)
		exit_with_error(FILE_ERR, pipex);
	return (fd);
}

void	close_fd(int fd)
{
	if (fd != 0)
		if (close(fd) == -1)
			exit_with_error(CLOSE_ERR, NULL);
}

t_pipex	*init_pipex(int argc, char **argv, char **env)
{
	char	**all_cmds;
	t_pipex	*pipex;

	all_cmds = get_all_commands(argc, argv);
	pipex = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex)
		exit_with_error(MALLOC_ERR, NULL);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->output = get_output_path(argc, argv, pipex);
		pipex->out_fd = open_file(pipex->output, 0, pipex);
		pipex->infile = ft_strdup("");
		pipex->in_fd = open_file(pipex->infile, 3, pipex);
	}
	else
	{
		pipex->output = get_output_path(argc, argv, pipex);
		pipex->out_fd = open_file(pipex->output, 1, pipex);
		pipex->infile = get_infile_path(argv, pipex);
		pipex->in_fd = open_file(pipex->infile, 2, pipex);
	}
	pipex->cmds = fill_cmd(all_cmds, env);
	free_strs(all_cmds);
	return (pipex);
}

int	duplicate_fd(int old, int new)
{
	if (dup2(old, new) == -1)
		return (ERROR);
	close_fd(old);
	return (OK);
}