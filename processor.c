/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:17:10 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/11 21:38:46 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static t_list	*process_commands(char *command);
static t_list	*process_infile(char **args, int *index, t_command_type type);
char			*format_path(char *command);
t_command_type	get_cmd_type(char **args, int argc, int index);

t_list	*process(int argc, char **args)
{
	t_list	*cmds;
	t_list	*new_cmd_node;
	int		i;

	i = 0;
	cmds = NULL;
	while (++i < argc)
	{
		if (i == 1 || i == argc - 1)
			new_cmd_node = process_infile(args, &i, get_cmd_type(args, argc,
						i));
		else
			new_cmd_node = process_commands(args[i]);
		if (!new_cmd_node)
		{
			errno = ENOMEM;
			ft_lstclear(&cmds, free);
			return (NULL);
		}
		ft_lstadd_back(&cmds, new_cmd_node);
	}
	return (cmds);
}

char	*format_path(char *command)
{
	char	*path_name;
	char	*tmp;
	int		i;

	i = 0;
	while (command[i])
	{
		if (ft_isspace(command[i]))
			break ;
		i++;
	}
	if (command[i])
		path_name = ft_substr(command, 0, i);
	else
		path_name = ft_strdup(command);
	if (!path_name)
		return (NULL);
	tmp = path_name;
	path_name = ft_strjoin("/bin/", path_name);
	free(tmp);
	return (path_name);
}

t_list	*process_commands(char *command)
{
	t_list	*processed;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = CMD;
	cmd->cmd = ft_split(command, ' ');
	if (!cmd->cmd)
		return (NULL);
	cmd->path_name = format_path(command);
	if (!cmd->path_name)
		return (NULL);
	processed = ft_lstnew(cmd);
	return (processed);
}

t_list	*process_infile(char **args, int *index, t_command_type type)
{
	t_list	*processed;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = type;
	if (type == HERE_DOC)
		*index += 1;
	cmd->path_name = ft_strdup(args[*index]);
	cmd->cmd = NULL;
	processed = ft_lstnew(cmd);
	return (processed);
}

t_command_type	get_cmd_type(char **args, int argc, int index)
{
	if (index == argc - 1)
		return (OUTFILE);
	else if (index == 1 && !ft_strncmp(args[index], "here_doc",
			ft_strlen("here_doc")))
		return (HERE_DOC);
	else
		return (INFILE);
}
