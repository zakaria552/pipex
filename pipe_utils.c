/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:15:31 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/11 20:16:10 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	close_pipe(int pipe[2])
{
	if (close(pipe[0]) < 0 || close(pipe[1]))
	{
		perror("Pipex: ");
	}
}

void	print_here_doc_input_msg(int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		ft_printf("pipe ");
	ft_printf("heredoc> ");
}
