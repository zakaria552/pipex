CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = pipe.c stdin_utils.c
NAME = pipex

all: $(NAME)

$(NAME):
	$(CC) $(FILES) libft/libft -o $(NAME)

clean:
	rm $(NAME)

fclean: clean

re: fclean all