CC = cc
CFLAGS = -Wall -Wextra -Werror
DIR_SRC = ./src/
SRC = $(addprefix $(DIR_SRC), main.c pipe.c pipe_utils.c execute.c processor.c format_path.c io_utils.c error_handler.c cmd_utils.c)
OBJ= $(SRC:.c=.o)
BONUS_OBJ= $(SRC_BONUS:.c=.o)
NAME = pipex
BONUS_NAME = pipex_bonus
libft_dir = libft
libft = $(libft_dir)/libft

all: $(NAME)

$(NAME): $(OBJ) $(libft)
	@echo "Building..."	
	@$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)
	@echo "Done building"

$(DIR_SRC)%.o: $(DIR_SRC)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(libft):
	@make -C $(libft_dir)

clean:
	@rm -f $(OBJ)
	@make clean -C $(libft_dir)

fclean: clean
	@rm -f $(NAME)
	make fclean -C $(libft_dir)

re: fclean all

.PHONY: clean fclean re