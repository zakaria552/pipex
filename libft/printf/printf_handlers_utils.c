/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handlers_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:54:53 by zfarah            #+#    #+#             */
/*   Updated: 2025/05/14 09:41:56 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

int	print_str(char *str, bool should_free)
{
	ssize_t	bytes_written;

	bytes_written = 0;
	if (!str)
		return (write(1, "(null)", 6));
	bytes_written = write(1, str, ft_strlen(str));
	if (should_free)
		free(str);
	return (bytes_written);
}

int	print_c(int c)
{
	char	character;

	character = (char)c;
	return (write(1, &character, 1));
}

void	rev_hex_str(char *str)
{
	char	tmp;
	int		i;
	int		len;

	len = ft_strlen(str) - 1;
	i = 0;
	while (i < len)
	{
		if (!str[len])
		{
			len--;
			continue ;
		}
		tmp = str[len];
		str[len] = str[i];
		str[i] = tmp;
		len--;
		i++;
	}
}
