/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:12:52 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/12 18:15:26 by zfarah           ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd_list;
	int		num_cmd;
	int		*pids;
	int		status;

	validate_num_args(argc, argv);
	cmd_list = process(argc, argv, envp);
	if (!cmd_list)
		exit_err(NULL, NULL, errno);
	num_cmd = ft_lstsize(cmd_list);
	if (!cmds_validated(cmd_list))
		exit_err(NULL, &cmd_list, errno);
	pids = ft_calloc(num_cmd - 1, sizeof(int));
	if (!pids)
		exit_err("Pipex: Failed to allocate resource", &cmd_list, ENOMEM);
	pipex(num_cmd, &cmd_list, pids);
	ft_lstclear(&cmd_list, (void *)free_cmd);
	wait_for_child_processes(pids, num_cmd - 2, &status);
	free(pids);
	return (WEXITSTATUS(status));
}
