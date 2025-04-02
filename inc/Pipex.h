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

enum e_bool
{
	OK = 0,
	ERROR = 1
};

typedef struct s_fds
{
	int	in;
	int	out;
}		t_fds;

/* app.core.parse_args.c functions */
void	execute_cmd(char *argv, char **env, t_fds *fds);
char	*find_path(char *cmd, char **env);
void	close_fd(int fd, t_fds *fds);
void	exit_with_error(t_fds *fds);

/* app._exec_pipex.c functions */
void	exec_pipex(char **argv, char **envp, t_fds *fds);

/* app._exec_pipex_bonus.c functions */
void	exec_multiple_cmd_heredoc(int argc, char **argv, char **env,
			t_fds *fds);
void	here_doc_parent_process(int *fd, t_fds *fds);
int		duplicate_fd(int old, int new);
int		open_file(char *path, char flag);

#endif
