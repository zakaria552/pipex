/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:05:06 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:24:30 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joint = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joint)
		return (NULL);
	ft_memmove(joint, (void *)s1, s1_len);
	ft_memmove(joint + s1_len, (void *)s2, s2_len);
	joint[s1_len + s2_len] = '\0';
	return (joint);
}
