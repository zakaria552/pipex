/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:47:31 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/17 17:29:15 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

static bool	map_infile_to_pipe(t_list **cmd_list, int pipe[2]);
static bool	map_stdin_to_pipe(char *limiter, int pipe[0], int num_pipes);
static bool	map_file_to_pipe(t_cmd *cmd, int pipe[2]);

void	pipex(t_list **cmd_list, int (*pipes)[2], int *pids)
{
	t_list	*tmp_cmd_list;
	int		i;

	tmp_cmd_list = *cmd_list;
	if (pipe(pipes[0]) < 0)
		return (pipe_error("Pipex: ", NULL, NULL));
	map_infile_to_pipe(&tmp_cmd_list, pipes[0]);
	i = 0;
	while (tmp_cmd_list && tmp_cmd_list->next != NULL)
	{
		if (pipe(pipes[i + 1]) < 0)
			return (pipe_error("Pipex: ", pipes[i], pipes[i + 1]));
		pids[i] = fork();
		if (pids[i] < 0)
			return (pipe_error("Pipex: ", pipes[i], pipes[i + 1]));
		if (pids[i] == 0)
		{
			execute(tmp_cmd_list->content, pipes + i);
			clean_up(cmd_list, pipes, pids);
			exit(errno);
		}
		close_pipe(pipes[i++]);
		tmp_cmd_list = tmp_cmd_list->next;
	}
	dump_to_outfile(tmp_cmd_list->content, pipes[i], (*cmd_list)->content);
}

bool	map_stdin_to_pipe(char *limiter, int pipe[0], int num_pipes)
{
	char	*line;
	size_t	len_limitter;

	len_limitter = ft_strlen(limiter);
	while (true)
	{
		print_here_doc_input_msg(num_pipes);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (false);
		if (ft_strncmp(line, limiter, len_limitter) == 0
			&& !line[len_limitter + 1])
			break ;
		if (write(pipe[1], line, ft_strlen(line)) < 0)
		{
			free(line);
			return (false);
		}
		free(line);
	}
	free(line);
	return (true);
}

bool	map_file_to_pipe(t_cmd *cmd, int pipe[2])
{
	int	fd;

	if (access(cmd->path_name, R_OK) < 0)
	{
		ft_printf("Pipex: %s: %s\n", strerror(errno), cmd->path_name);
		errno = 0;
		return (false);
	}
	fd = open(cmd->path_name, O_RDONLY);
	if (fd < 0)
		return (false);
	if (dup2(fd, pipe[0]) < 0)
	{
		close(fd);
		perror("Pipex: %s");
		return (false);
	}
	close(fd);
	return (true);
}

bool	map_infile_to_pipe(t_list **cmd_list, int pipe[2])
{
	t_cmd	*cmd;

	cmd = (*cmd_list)->content;
	*cmd_list = (*cmd_list)->next;
	if (cmd->type == HERE_DOC)
		return (map_stdin_to_pipe(cmd->path_name, pipe, ft_lstsize(*cmd_list)
				- 1));
	else
		return (map_file_to_pipe(cmd, pipe));
}
