/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:08:42 by mbah              #+#    #+#             */
/*   Updated: 2025/02/04 14:58:11 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

# define RED         "\033[1;31m"
# define RESET       "\033[0m"

# define MALLOC_ERR   "Error: malloc failed -> "
# define ARG_ERR      "Error: invalid number of arguments -> "
# define FILE_ERR     "Error: file cannot be opened -> "
# define PIPE_ERR     "Error: pipe failed -> "
# define FORK_ERR     "Error: fork failed -> "
# define EXEC_ERR     "Error: command not found or cannot be executed -> "
# define SYNTAX_ERR   "Error: invalid syntax -> "
# define PATH_ERR     "Error: PATH not found -> "
# define DUP2_ERR     "Error: dup2 failed -> "
# define CLOSE_ERR    "Error: close failed -> "
# define WAIT_ERR     "Error: waitpid failed -> "

enum e_bool
{
	OK = 0,
	ERROR = 1
};

#endif
