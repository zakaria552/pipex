CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main.c pipe.c pipe_utils.c execute.c helpers.c processor.c format_path.c io_utils.c error_handler.c cmd_utils.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
NAME = pipex
libft_dir = libft
libft = $(libft_dir)/libft

all: $(NAME)

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(libft):
	$(MAKE) -C $(libft_dir)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all