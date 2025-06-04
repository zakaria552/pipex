#include "pipe.h"

static t_list *process_commands(char *command);
static t_list *process_infile(char *infile);

t_list *process(int argc, char **args)
{
	t_list *cmds;
	t_list *new_cmd_node;
	int i;
	
	i = 0;
	cmds = NULL;
	while (++i < argc)
	{
		printf("i:%d-%s\n", i, args[i]);
		if (i == 1 || i == argc - 1)	
			new_cmd_node = process_infile(args[i]);
		else 
			new_cmd_node = process_commands(args[i]);
		if (!new_cmd_node)
		{
			ft_lstclear(&cmds, free);
			return (NULL);
		}
		ft_lstadd_back(&cmds, new_cmd_node);
	}
	return cmds;
}
	
t_list *process_commands(char *command)
{
	t_list *processed;
	t_cmd *cmd;
	int i;
	
	cmd = malloc(sizeof(t_cmd)); 
	i = 0;
	cmd->type = CMD;
	cmd->cmd = ft_strdup(command);
	while (command[i])
	{
		if (ft_isspace(command[i]))
			break;
		i++;
	}
	if (command[i])
		cmd->name = ft_substr(command, 0, i);
	else
		cmd->name = ft_strdup(command);
	if (!cmd->name)
		return NULL;
	processed = ft_lstnew(cmd);
	if (!processed)
		free(cmd->name);
	return (processed);
}
t_list *process_infile(char *infile)
{
	t_list *processed;
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd)); 
	cmd->type = INFILE;
	cmd->name = ft_strdup(infile);
	cmd->cmd = NULL;
	processed = ft_lstnew(cmd);
	return (processed);
}