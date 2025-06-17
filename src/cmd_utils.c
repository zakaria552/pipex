/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:18:38 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/17 17:13:31 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	char	**cmd_flags;

	cmd_flags = cmd->cmd;
	i = 0;
	while (cmd_flags && cmd_flags[i])
	{
		free(cmd_flags[i]);
		i++;
	}
	free(cmd_flags);
	free(cmd->path_name);
	free(cmd);
}

void	*free_matrix_mem(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

bool	cmds_validated(t_list *cmds)
{
	t_cmd	*cmd;

	while (cmds && cmds->next)
	{
		cmd = cmds->content;
		if (cmd->type == CMD && !cmd->path_name)
			return (false);
		cmds = cmds->next;
	}
	return (true);
}

void	validate_num_args(int argc)
{
	if (argc - 1 < 4 || argc > 5)
		exit_err("Pipex: Usage ./pipex infile cmd1 cmd2 outfile", NULL,
			EINVAL);
}
