/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:18:38 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/11 21:30:39 by zfarah           ###   ########.fr       */
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
