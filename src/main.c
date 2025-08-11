/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:12:52 by zfarah            #+#    #+#             */
/*   Updated: 2025/08/11 10:38:17 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	wait_for_child_processes(int *pids, int num_process, int *status)
{
	int	i;

	i = -1;
	while (++i < num_process)
		waitpid(pids[i], status, 0);
}

bool	clean_up(t_list **cmd_list, int (*pipes)[2], int *pids)
{
	if (cmd_list)
		ft_lstclear(cmd_list, (void *)free_cmd);
	if (pipes)
		free(pipes);
	if (pids)
		free(pids);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd_list;
	int		num_cmd;
	int		*pids;
	int		status;
	int		(*pipes)[2];

	validate_num_args(argc, argv);
	cmd_list = process(argc, argv, envp);
	if (!cmd_list)
		exit_err(NULL, NULL, errno);
	num_cmd = ft_lstsize(cmd_list);
	pids = ft_calloc(num_cmd - 1, sizeof(int));
	if (!pids)
		exit_err("Pipex: Failed to allocate resource", &cmd_list, ENOMEM);
	pipes = malloc((num_cmd - 1) * sizeof(int [2]));
	if (!pipes && clean_up(NULL, NULL, pids))
		exit_err("Pipex: Failed to allocate resource", &cmd_list, ENOMEM);
	pipex(&cmd_list, pipes, pids);
	wait_for_child_processes(pids, num_cmd - 2, &status);
	clean_up(&cmd_list, pipes, pids);
	if (errno > 0)
		return (errno);
	return (WEXITSTATUS(status));
}
