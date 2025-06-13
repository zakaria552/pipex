/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:18:38 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/13 13:58:15 by zfarah           ###   ########.fr       */
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

void	validate_num_args(int argc, char **args)
{
	bool	is_here_doc;

	if (argc > 1 && ft_strncmp(args[1], "here_doc", ft_strlen("here_doc")) == 0)
		is_here_doc = true;
	else
		is_here_doc = false;
	if (is_here_doc && argc - 1 < 5)
		exit_err("Pipex: Usage ./pipex here_doc LIMITER cmd1 cmd2 ... outfile",
			NULL, EINVAL);
	else if (argc - 1 < 4)
		exit_err("Pipex: Usage ./pipex infile cmd1 cmd2 ... outfile", NULL,
			EINVAL);
}
