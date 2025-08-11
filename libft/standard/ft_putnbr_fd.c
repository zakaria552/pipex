/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:10:19 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:09:37 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"
#include <unistd.h>
#include <limits.h>

static void	recursively_putnbr_fd(int n, int fd)
{
	if (n >= 10)
		recursively_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	recursively_putnbr_fd(n, fd);
}
