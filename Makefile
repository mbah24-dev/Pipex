# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 16:08:05 by mbah              #+#    #+#              #
#    Updated: 2025/02/04 21:39:50 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      ?= pipex
CC         = cc
DIR        = src
INC        = inc
LIBFT_H    = lib/libft/libft.h
LIBFT_A    = lib/libft/libft.a
CFLAGS     = -Wall -Werror -Wextra -I $(INC) -g3
HEADER     = $(INC)/Pipex.h $(INC)/libft.h  $(LIBFT_H)
SRC        = $(DIR)/app/core/app.core.parser/app.core.fill_cmd.c $(DIR)/app/core/app.core.parser/app.core.parse_args.c $(DIR)/app/core/app.core.free_pipex/app.core.cleanup.c \
			 $(DIR)/app/core/app.core.free_pipex/app.core.free_strs.c $(DIR)/main.c 

OBJS       = $(SRC:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

# Règle pour créer la bibliothèque libft.a
$(LIBFT_A): $(HEADER)
	$(MAKE) -C lib/libft

# Clean les objets et la bibliothèque libft.a et pipex
clean:
	$(MAKE) clean -C lib/libft
	rm -rf $(OBJS)

# Supprime tout (objets, executable, et libft.a et pipex)
fclean: clean
	$(MAKE) fclean -C lib/libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
