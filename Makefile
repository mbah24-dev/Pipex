NAME      ?= Pipex
CC         = cc
DIR        = src
INC        = inc
CFLAGS     = -Wall -Werror -Wextra -I ./
HEADER     = $(INC)/Pipex.h 
SRC        = $(DIR)/app/core/core.hello_word.c $(DIR)/main.c 

OBJS       = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
