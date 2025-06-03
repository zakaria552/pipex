CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = pipe.c stdin_utils.c
NAME = pipex
libft_dir = libft
libft = $(libft_dir)/libft
all: $(NAME)

$(NAME): $(libft)
	$(CC) $(FILES) libft/libft -o $(NAME)

$(libft): $(libft_dir)
	$(MAKE) -C $(libft_dir)

clean:
	rm $(NAME)

fclean: clean

re: fclean all