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

