CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main.c pipe.c helpers.c processor.c stdin_utils.c
NAME = pipex
libft_dir = libft
libft = $(libft_dir)/libft
all: $(NAME)

$(NAME): $(libft)
	$(CC) $(FILES) libft/libft -o $(NAME)

$(libft): $(libft_dir)
	$(MAKE) -C $(libft_dir)

main: $(libft)
	$(CC) -g $(FILES) libft/libft -o main

clean:
	rm $(NAME) main

fclean: clean

re: fclean all