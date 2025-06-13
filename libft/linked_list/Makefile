CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \

OBJ = $(addprefix ../obj/, $(CFILES:.c=.o))

all: $(OBJ)

../obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ)

re: fclean all