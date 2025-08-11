/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:16:09 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:05:19 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

static int	str_num_length(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char	*str_num;
	int		str_len;
	int		sign;
	long	n;

	str_len = str_num_length(num);
	str_num = malloc((str_len + 1) * sizeof(char));
	sign = 1;
	n = num;
	if (!str_num)
		return (NULL);
	str_num[str_len] = '\0';
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	while (--str_len >= 0)
	{
		str_num[str_len] = n % 10 + '0';
		n = n / 10;
		if (str_len == 0 && sign < 0)
			str_num[0] = '-';
	}
	return (str_num);
}
