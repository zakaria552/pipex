CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main.c pipe.c pipe_utils.c execute.c helpers.c processor.c format_path.c io_utils.c error_handler.c cmd_utils.c
OBJ = $(FILES:.c=.o)
NAME = pipex
libft_dir = libft
libft = $(libft_dir)/libft

all: $(NAME)

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(libft):
	make -C $(libft_dir)

clean:
	rm -f $(OBJ)
	make clean -C $(libft_dir)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(libft_dir)

re: fclean all