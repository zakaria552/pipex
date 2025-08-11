/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:43:58 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/13 14:19:03 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *buffer, char **dump, char *chunk, int *malloc_fail);
static char	*get_first_line(char *buffer, char **dump, int fd,
				int *malloc_fail);
static void	save_remaining_data(char *buffer, char *ptr_line);

char	*get_next_line(int fd)
{
	static char	buffers[1024][BUFFER_SIZE + 1];
	char		*line;
	char		*dump;
	int			malloc_fail;

	malloc_fail = 0;
	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffers[fd][0])
		line = get_line(buffers[fd], NULL, NULL, &malloc_fail);
	if (line || malloc_fail)
		return (line);
	dump = ft_substr(buffers[fd], 0, BUFFER_SIZE + 1);
	if (!dump)
		return (NULL);
	line = get_first_line(buffers[fd], &dump, fd, &malloc_fail);
	free(dump);
	return (line);
}

static char	*get_line(char *buffer, char **dump, char *chunk, int *malloc_fail)
{
	char	*line;
	char	*ptr_line;
	char	*buffer_to_look;

	if (dump != NULL)
		buffer_to_look = *dump;
	else
		buffer_to_look = buffer;
	ptr_line = ft_strchr(buffer_to_look, '\n');
	if (!ptr_line)
	{
		if (dump != NULL)
			ft_memset(chunk, 0, BUFFER_SIZE);
		return (NULL);
	}
	line = ft_substr(buffer_to_look, 0, ptr_line - buffer_to_look + 1);
	if (!line)
	{
		*malloc_fail = 1;
		return (NULL);
	}
	save_remaining_data(buffer, ptr_line);
	return (line);
}

static char	*get_first_line(char *buffer, char **dump, int fd, int *malloc_fail)
{
	char	chunk[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*line;
	char	*tmp;

	ft_memset(chunk, 0, BUFFER_SIZE + 1);
	bytes_read = read(fd, chunk, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		tmp = ft_strjoin(*dump, chunk);
		if (!*tmp)
			return (NULL);
		free(*dump);
		*dump = tmp;
		line = get_line(buffer, dump, chunk, malloc_fail);
		if (line || *malloc_fail)
			return (line);
		bytes_read = read(fd, chunk, BUFFER_SIZE);
	}
	if (bytes_read == 0 && **dump)
	{
		ft_memset(buffer, 0, BUFFER_SIZE);
		return (ft_substr(*dump, 0, ft_strlen(*dump)));
	}
	return (NULL);
}

static void	save_remaining_data(char *buffer, char *ptr_line)
{
	int	len;

	if (*(ptr_line + 1) == '\0')
	{
		ft_memset(buffer, 0, BUFFER_SIZE);
		return ;
	}
	len = ft_strlen(ptr_line + 1);
	ft_memmove(buffer, ptr_line + 1, len);
	while (buffer[len])
	{
		buffer[len] = 0;
		len++;
	}
}
