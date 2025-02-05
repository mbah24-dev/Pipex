/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:59:16 by mbah              #+#    #+#             */
/*   Updated: 2024/12/09 20:36:12 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE >= 9223372036854775807
#  undef BUFFER_SIZE 
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
void	read_line_from_file(int fd, char **stash, char **temp_buffer);
char	*parse_line_content(char **stash, char **line_data);
char	*extract_before_newline(const char *string);
char	*extract_after_newline(const char *string);

/*======== (gnl utils) =========*/
int		has_newline_in_str(const char *string);
char	*duplicate_string(const char *original_string);
char	*join_strings(const char *first_string, const char *second_string);
void	*allocate_zeroed_memory(size_t element_count, size_t element_size);
void	free_string_pointers(char **string1, char **string2, char **string3);

#endif