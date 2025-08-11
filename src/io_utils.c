/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:14:00 by zfarah            #+#    #+#             */
/*   Updated: 2025/08/11 10:38:17 by zfarah           ###   ########.fr       */
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
		ft_printf("Pipex: %s: %s\n", strerror(errno), outfile_cmd->path_name);
		close_pipe(pipe);
		set_errno(1);
		return ;
	}
	close(pipe[1]);
	if (read_write_file(pipe[0], fd) < 0)
		ft_printf("Pipex: %s\n", strerror(errno));
	close(fd);
	close(pipe[0]);
}
