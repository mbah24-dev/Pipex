# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 16:08:05 by mbah              #+#    #+#              #
#    Updated: 2025/02/06 19:05:11 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      ?= pipex
CC         = cc
DIR        = src
INC        = inc
LIBFT_H    = lib/libft/libft.h
LIBFT_A    = lib/libft/libft.a
CFLAGS     = -Wall -Werror -Wextra -I $(INC) -g3
HEADER     = $(INC)/Pipex.h $(INC)/libft.h  $(LIBFT_H) $(INC)/get_next_line.h 
SRC        = $(DIR)/app/core/app_parser/app_fill_cmd.c $(DIR)/app/core/app_parser/app_parse_args.c $(DIR)/app/core/app_execute/app_exec_pipex.c \
			 $(DIR)/app/core/app_free/app_cleanup.c $(DIR)/app/core/app_free/app_free_strs.c $(DIR)/main.c \
			 ./lib/gnl/get_next_line.c ./lib/gnl/get_next_line_utils.c 

B_SRC      =  $(DIR)/app/core/app_parser/app_fill_cmd.c $(DIR)/app/core/app_parser/app_parse_args.c \
			 $(DIR)/app/core/app_free/app_cleanup.c $(DIR)/app/core/app_free/app_free_strs.c  \
			 ./lib/gnl/get_next_line.c ./lib/gnl/get_next_line_utils.c $(DIR)/app/core/app_bonus_part/app_exec_pipex_bonus.c \
			  $(DIR)/app/core/app_bonus_part/app_exec_pipex_utils_bonus.c
			 
OBJS       = $(SRC:.c=.o)

B_OBJS       = $(B_SRC:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

bonus: $(B_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT_A) -o $(NAME)

$(LIBFT_A): $(HEADER)
	$(MAKE) -C lib/libft

clean:
	$(MAKE) clean -C lib/libft
	rm -rf $(OBJS) $(B_OBJS) 

fclean: clean
	$(MAKE) fclean -C lib/libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
