/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:31:32 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/12 20:07:13 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	pipe_error(char *msg, int current_pipe[2], int next_pipe[2])
{
	if (current_pipe)
		close_pipe(current_pipe);
	if (next_pipe)
		close_pipe(next_pipe);
	if (msg)
		perror(msg);
	perror("Pipex: %s");
}

void	exit_err(char *msg, t_list **cmd_list, int err_code)
{
	errno = err_code;
	if (cmd_list)
		ft_lstclear(cmd_list, (void *)free_cmd);
	if (msg)
		perror(msg);
	exit(errno);
}

void	*set_errno(int err_code)
{
	errno = err_code;
	return NULL;
}