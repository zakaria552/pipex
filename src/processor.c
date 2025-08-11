/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:17:10 by zfarah            #+#    #+#             */
/*   Updated: 2025/08/11 10:37:45 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static t_list			*process_commands(char *command, char **envp);
static t_list			*process_infile(char **args, int *index,
							t_command_type type);
static t_command_type	get_cmd_type(char **args, int argc, int index);

t_list	*process(int argc, char **args, char **envp)
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
			new_cmd_node = process_commands(args[i], envp);
		if (!new_cmd_node)
		{
			ft_lstclear(&cmds, free);
			return (NULL);
		}
		ft_lstadd_back(&cmds, new_cmd_node);
	}
	return (cmds);
}

static t_list	*process_commands(char *cmd_arg, char **envp)
{
	t_list	*processed;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (set_errno(ENOMEM));
	cmd->cmd = ft_split(cmd_arg, ' ');
	if (!cmd->cmd)
	{
		free(cmd);
		return (set_errno(ENOMEM));
	}
	cmd->type = CMD;
	cmd->envp = envp;
	cmd->path_name = NULL;
	processed = ft_lstnew(cmd);
	if (!processed)
	{
		free_matrix_mem(cmd->cmd);
		free(cmd);
	}
	return (processed);
}

static t_list	*process_infile(char **args, int *index, t_command_type type)
{
	t_list	*processed;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = type;
	if (type == HERE_DOC)
		*index += 1;
	cmd->path_name = ft_strdup(args[*index]);
	if (!cmd->path_name)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd = NULL;
	cmd->envp = NULL;
	processed = ft_lstnew(cmd);
	if (!processed)
	{
		free(cmd->path_name);
		free(cmd);
	}
	return (processed);
}

static t_command_type	get_cmd_type(char **args, int argc, int index)
{
	if (index == argc - 1)
		return (OUTFILE);
	else if (index == 1 && !ft_strncmp(args[index], "here_doc",
			ft_strlen("here_doc")))
		return (HERE_DOC);
	else
		return (INFILE);
}
