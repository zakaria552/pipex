/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:09:11 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:22:21 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*arr;

	if (nitems != 0 && (nitems * size) / nitems != size)
	{
		return (NULL);
	}
	arr = malloc(nitems * size);
	if (arr == 0)
	{
		return (NULL);
	}
	ft_memset(arr, 0, nitems * size);
	return (arr);
}
