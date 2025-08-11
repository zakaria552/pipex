CC = cc
FLAGS = -Wall -Wextra -Werror
CFILES = ft_printf.c printf_handlers.c printf_handlers_utils.c
OBJ = $(addprefix ../obj/, $(CFILES:.c=.o))

all: $(OBJ)

../obj/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

re:	fclean all

.PHONY: all clean re