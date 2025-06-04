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


void print_cmd_list(t_list *head)
{
	t_cmd *cmds;
	int i;

	i = 0;
	while(head != NULL)
	{
		cmds = head->content;
		ft_printf("--%d-->[cmd: %s, name: %s, type: %s]\n", i, cmds->cmd, cmds->name, get_enum_type(cmds->type));
		head = head->next;
		i++;
	}
}

