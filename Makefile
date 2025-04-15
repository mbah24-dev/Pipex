# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 16:08:05 by mbah              #+#    #+#              #
#    Updated: 2025/02/17 14:33:31 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      ?= pipex
CC         = cc
DIR        = src
INC        = inc
CFLAGS     = -Wall -Werror -Wextra -I $(INC)
HEADER     = $(INC)/pipex.h $(INC)/get_next_line.h 
SRC        = $(DIR)/app/core/app_parser/app_parse_args.c $(DIR)/app/core/app_execute/app_exec_pipex.c \
			 $(DIR)/main.c ./lib/ft_putstr_fd.c ./lib/ft_split.c \
			 ./lib/ft_strjoin.c ./lib/ft_strnstr.c 
			 
OBJS       = $(SRC:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
