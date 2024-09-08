# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex

# Files
SRC = pipex.c utils.c
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
