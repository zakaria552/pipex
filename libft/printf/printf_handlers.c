/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:22:57 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/02 12:36:12 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_case(unsigned long num, bool capitalize)
{
	char	*hexs;
	int		i;
	char	a;

	if (num == 0)
		return (print_c('0'));
	hexs = ft_calloc((sizeof(unsigned long) * CHAR_BIT) / 4 + 1, sizeof(char));
	if (!hexs)
		return (-1);
	a = 'a';
	if (capitalize)
		a = 'A';
	i = 0;
	while (num > 0)
	{
		if (num % 16 < 10)
			hexs[i] = (num % 16) + '0';
		else
			hexs[i] = a + ((num % 16) - 10);
		num = num / 16;
		i++;
	}
	rev_hex_str(hexs);
	return (print_str(hexs, true));
}

int	print_ptr(void *ptr)
{
	unsigned long	addr;
	int				len;
	int				hex_written_bytes;

	addr = (unsigned long)ptr;
	if (!ptr)
		return (print_str("(nil)", false));
	len = print_str("0x", false);
	if (len == -1)
		return (len);
	hex_written_bytes = print_hex_case(addr, false);
	if (hex_written_bytes == -1)
		return (hex_written_bytes);
	len += hex_written_bytes;
	return (len);
}

int	print_int(int num)
{
	char	*str;

	str = ft_itoa(num);
	if (!str)
		return (-1);
	return (print_str(str, true));
}

int	print_unsigned_int(unsigned int num)
{
	char	*str;

	str = ft_uitoa(num);
	if (!str)
		return (-1);
	return (print_str(str, true));
}
