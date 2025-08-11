/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:42:16 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/23 12:30:37 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s) + 1;
	str = malloc(size * sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s, size);
	return (str);
}
