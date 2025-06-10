#include "pipe.h"

static t_list *process_commands(char *command);
static t_list *process_infile(char **args, int *index, e_command_type type);
char *format_path(char *command);

e_command_type get_type(char **args, int argc, int index)
{
	if (index == argc - 1)
		return OUTFILE;
	else if (index == 1 && !ft_strncmp(args[index], "here_doc", ft_strlen("here_doc")))
		return HERE_DOC;
	else
		return INFILE;
}

t_list *process(int argc, char **args)
{
	t_list *cmds;
	t_list *new_cmd_node;
	int i;
	
	i = 0;
	cmds = NULL;
	while (++i < argc)
	{
		if (i == 1 || i == argc - 1)	
			new_cmd_node = process_infile(args, &i, get_type(args, argc, i));
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
char *format_path(char *command)
{
	char *path_name;
	char *tmp;
	int i;
	
	i = 0;
	while (command[i])
	{
		if (ft_isspace(command[i]))
			break;
		i++;
	}
	if (command[i])
		path_name = ft_substr(command, 0, i);
	else
		path_name = ft_strdup(command);
	if (!path_name)
		return NULL;
	tmp = path_name;
	path_name = ft_strjoin("/bin/", path_name);
	free(tmp);
	return (path_name);
}
t_list *process_commands(char *command)
{
	t_list *processed;
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->type = CMD;
	cmd->cmd = ft_split(command, ' ');
	if (!cmd->cmd)
		return NULL;
	cmd->path_name = format_path(command);
	if (!cmd->path_name)
		return NULL;
	processed = ft_lstnew(cmd);
	return (processed);
}
t_list *process_infile(char **args, int *index, e_command_type type)
{
	t_list *processed;
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = type;
	if (type == HERE_DOC)
		*index += 1;
	cmd->path_name = ft_strdup(args[*index]);
	cmd->cmd = NULL;
	processed = ft_lstnew(cmd);
	return (processed);
}

void free_cmd(t_cmd *cmd)
{
	int i;
    char **cmd_flags;
    
    cmd_flags = cmd->cmd;
	i = 0;
	while(cmd_flags && cmd_flags[i])
    {
		free(cmd_flags[i]);
        i++;
    }
    free(cmd_flags);
	free(cmd->path_name);
    free(cmd);
}