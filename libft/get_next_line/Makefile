FILES=get_next_line.c
OBJ=$(addprefix ../obj/, $(FILES:.c=.o))
FLAGS = -Wall -Wextra -Werror
CC = cc

all: $(OBJ)

../obj/%.o	: %.c
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJ)

re: clean all