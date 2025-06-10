#include "pipe.h"

char *get_enum_type(e_command_type type)
{
	if (type == INFILE)
		return "INFILE";
	else if (type == CMD)
		return "CMD";
	else 
		return "UNKNOWN";
}

void print_cmd(t_cmd *cmds)
{
	int j;
	char **args = cmds->cmd;

	j = 0;
		ft_printf("[cmd: ");
		while(args && args[j])
		{
			ft_printf("%s ", args[j]);
			j++;
		}
		ft_printf(", name: %s, type: %s]\n", cmds->path_name, get_enum_type(cmds->type));
}

void print_cmd_list(t_list *head)
{
	t_cmd *cmds;
	int i;
	int j;
	char **args;
	i = 0;

	while(head != NULL)
	{
		cmds = head->content;
		args = cmds->cmd;
		j = 0;
		ft_printf("--%d-->[cmd: ", i);
		while(args && args[j])
		{
			ft_printf("%s ", args[j]);
			j++;
		}
		ft_printf(", name: %s, type: %s]\n", cmds->path_name, get_enum_type(cmds->type));
		head = head->next;
		i++;
	}
}

void list_open_fds(char *from, int index) {
    int max_fd = sysconf(_SC_OPEN_MAX);

    printf("Open file descriptors:\n");
    for (int fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("[%s-%d] FD %d is open\n", from, index, fd);
        }
    }
}
