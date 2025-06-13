/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:22:41 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/13 14:23:54 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	is_valid_format(char c);
static int	print_format(char c, va_list *args);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		len;
	int		prev_len;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		prev_len = len;
		if (str[i] == '%' && is_valid_format(str[i + 1]))
			len += print_format(str[++i], &args);
		else
			len += print_c(str[i]);
		if (prev_len > len)
		{
			len = -1;
			break ;
		}
		i++;
	}
	va_end(args);
	return (len);
}

static bool	is_valid_format(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (true);
	return (false);
}

static int	print_format(char c, va_list *args)
{
	if (c == 'c')
		return (print_c(va_arg(*args, int)));
	if (c == 's')
		return (print_str(va_arg(*args, char *), false));
	if (c == 'p')
		return (print_ptr(va_arg(*args, void *)));
	if (c == 'd' || c == 'i')
		return (print_int(va_arg(*args, int)));
	if (c == 'u')
		return (print_unsigned_int(va_arg(*args, unsigned int)));
	if (c == 'x')
		return (print_hex_case(va_arg(*args, unsigned int), false));
	if (c == 'X')
		return (print_hex_case(va_arg(*args, unsigned int), true));
	if (c == '%')
		return (print_c('%'));
	return (0);
}
