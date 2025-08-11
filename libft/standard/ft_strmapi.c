/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:03:33 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:25:01 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*mapped;

	len = ft_strlen(s);
	mapped = malloc(len + 1);
	if (!mapped)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = f(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
