/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:23:03 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/11 21:38:46 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*get_enum_type(t_command_type type)
{
	if (type == INFILE)
		return ("INFILE");
	else if (type == CMD)
		return ("CMD");
	else
		return ("UNKNOWN");
}

void	print_cmd(t_cmd *cmds)
{
	int		j;
	char	**args;

	args = cmds->cmd;
	j = 0;
	ft_printf("[cmd: ");
	while (args && args[j])
	{
		ft_printf("%s ", args[j]);
		j++;
	}
	ft_printf(", name: %s, type: %s]\n", cmds->path_name,
		get_enum_type(cmds->type));
}

void	print_cmd_list(t_list *head)
{
	t_cmd	*cmds;
	int		i;
	int		j;
	char	**args;

	i = 0;
	while (head != NULL)
	{
		cmds = head->content;
		args = cmds->cmd;
		j = 0;
		ft_printf("--%d-->[cmd: ", i);
		while (args && args[j])
		{
			ft_printf("%s ", args[j]);
			j++;
		}
		ft_printf(", name: %s, type: %s]\n", cmds->path_name,
			get_enum_type(cmds->type));
		head = head->next;
		i++;
	}
}

void	list_open_fds(char *from, int index)
{
	int	max_fd;
	int	fd;

	max_fd = sysconf(_SC_OPEN_MAX);
	fd = -1;
	printf("Open file descriptors:\n");
	while (++fd < max_fd)
	{
		if (fcntl(fd, F_GETFD) != -1)
		{
			printf("[%s-%d] FD %d is open\n", from, index, fd);
		}
	}
}
