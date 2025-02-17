/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:08:42 by mbah              #+#    #+#             */
/*   Updated: 2025/02/17 14:31:38 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

# define MALLOC_ERR   "Error: malloc failed "
# define ARG_ERR      "Error: invalid number of arguments "
# define FILE_ERR     "Error: file cannot be opened "
# define PIPE_ERR     "Error: pipe failed "
# define FORK_ERR     "Error: fork failed "
# define EXEC_ERR     "Error: command not found "
# define SYNTAX_ERR   "Error: invalid syntax "
# define PATH_ERR     "Error: PATH not found "
# define DUP2_ERR     "Error: dup2 failed "
# define CLOSE_ERR    "Error: close failed "
# define WAIT_ERR     "Error: waitpid failed "

enum e_bool
{
	OK = 0,
	ERROR = 1
};

typedef struct s_cmd
{
	char	*name;
	char	**args;
	char	*path;
}			t_cmd;

typedef struct s_pipex
{
	char	*infile;
	char	*output;
	int		in_fd;
	int		out_fd;
	t_cmd	*cmds;
}			t_pipex;

/* main.c functions */
void	exit_with_error(char *err_msg, t_pipex *pipex);
int		open_file(char *path, char flag, t_pipex *pipex);
void	close_fd(int fd);
t_pipex	*init_pipex(int argc, char **argv, char **env);

/* app.core.free_strs.c functions */
void	free_strs(char **strs);

/* app.core.parse_args.c functions */
char	*get_infile_path(char **argv, t_pipex *pipex);
char	**get_all_commands(int argc, char **argv);
char	*get_output_path(int argc, char **argv, t_pipex *pipex);
int		get_nb_pipes(t_pipex *pipex);

/* app.core.fill_cmd.c functions */
t_cmd	*fill_cmd(char **str_cmd, char **env);

/* app.core.cleanup.c functions */
void	clean_pipex(t_pipex *pipex);

/* app._exec_pipex.c functions */
void	exec_pipex(t_pipex *pipex);
int		execute_cmd(t_cmd cmd);
int		duplicate_fd(int old, int new);
void	child_process(t_pipex *pipex, int *fd, int cmd_idx);
void	parent_process(t_pipex *pipex, int *fd, int cmd_idx);

/* app._exec_pipex_bonus.c functions */
void	exec_multiple_cmd_heredoc(t_pipex *pipex, int argc, char **argv);

void	here_doc_parent_process(int *fd, t_pipex *pipex);

#endif
