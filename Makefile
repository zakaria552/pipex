CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = pipe.c
NAME = pipex

all: $(NAME)

$(NAME):
	$(CC) $(FILES) -o $(NAME)

clean:
	rm $(NAME)

fclean: clean

re: fclean all