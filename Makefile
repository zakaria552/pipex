CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main.c pipe.c pipe_utils.c execute.c helpers.c processor.c io_utils.c error_handler.c
NAME = pipex
libft_dir = libft
libft = $(libft_dir)/libft

all: $(NAME)

$(NAME): $(libft)
	$(CC) $(FILES) $(libft) -o $(NAME)

$(libft):
	$(MAKE) -C $(libft_dir)

clean:
	rm $(NAME)

fclean: clean

re: fclean all