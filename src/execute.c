/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:25:07 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/13 18:00:49 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute(t_cmd *command, int pipes[][2])
{
	int		*current_pipe;
	int		*next_pipe;
	char	*path;

	path = format_path(*(command->cmd), command->envp);
	current_pipe = pipes[0];
	next_pipe = pipes[1];
	if (!path)
	{
		close_pipe(current_pipe);
		close_pipe(next_pipe);
		return ;
	}
	if (dup2(current_pipe[0], STDIN_FILENO) < 0 || dup2(next_pipe[1],
			STDOUT_FILENO) < 0)
	{
		free(path);
		close_pipe(current_pipe);
		close_pipe(next_pipe);
		return ;
	}
	close_pipe(current_pipe);
	close_pipe(next_pipe);
	execve(path, command->cmd, command->envp);
	free(path);
}
