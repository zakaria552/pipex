/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:14:00 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/13 14:16:01 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

ssize_t	read_write_file(int fd, int write_fd)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	written_bytes;
	ssize_t	bytes_read;

	ft_memset(buff, 0, BUFFER_SIZE);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	written_bytes = bytes_read;
	while (bytes_read > 0)
	{
		if (write(write_fd, buff, bytes_read) < 0)
			return (-1);
		ft_memset(buff, 0, bytes_read);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		written_bytes += bytes_read;
	}
	if (bytes_read < 0)
		return (-1);
	return (written_bytes);
}

void	dump_to_outfile(t_cmd *outfile_cmd, int pipe[2], t_cmd *infile_cmd)
{
	int				fd;
	int				flags;
	t_command_type	infile_type;

	infile_type = infile_cmd->type;
	flags = O_CREAT | O_WRONLY | O_APPEND;
	if (infile_type != HERE_DOC)
		flags |= O_TRUNC;
	fd = open(outfile_cmd->path_name, flags, 0644);
	if (fd < 0)
	{
		close_pipe(pipe);
		ft_printf("Pipex: ", strerror(errno), outfile_cmd->path_name);
		return ;
	}
	close(pipe[1]);
	if (read_write_file(pipe[0], fd) < 0)
		ft_printf("Pipex: %s", strerror(errno));
	close(fd);
	close(pipe[0]);
}
