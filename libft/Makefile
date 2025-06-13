CC = cc 
NAME = libft
MODULES = standard printf linked_list get_next_line
OBJDIR = ./obj
OBJFILES = $(OBJDIR)/*.o

all: $(OBJDIR) $(OBJFILES) $(NAME)

$(OBJDIR):
	mkdir $@

$(OBJFILES): $(MODULES)

$(MODULES):
	$(MAKE) -C $@

$(NAME): $(OBJFILES)
	ar rcs $@ $^

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm $(NAME)

.PHONY: all $(MODULES) clean fclean