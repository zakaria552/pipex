CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(addprefix ./src/, main.c pipe.c pipe_utils.c execute.c helpers.c processor.c format_path.c io_utils.c error_handler.c cmd_utils.c)
SRC_BONUS = $(addprefix ./src_bonus/, main_bonus.c pipe_bonus.c pipe_utils_bonus.c execute_bonus.c helpers.c processor_bonus.c format_path_bonus.c io_utils_bonus.c error_handler_bonus.c cmd_utils_bonus.c)
OBJ= $(SRC:.c=.o)
BONUS_OBJ= $(SRC_BONUS:.c=.o)
NAME = pipex
BONUS_NAME = pipex_bonus
libft_dir = libft
libft = $(libft_dir)/libft

all: $(NAME)

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(libft)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(libft) -o $@

./src/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(libft):
	make -C $(libft_dir)

./src_bonus/%.o: ./src_bonus/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BONUS_OBJ)
	rm -f $(OBJ)
	make clean -C $(libft_dir)

fclean: clean
	rm -f $(BONUS_NAME) $(NAME)
	make fclean -C $(libft_dir)

re: fclean all