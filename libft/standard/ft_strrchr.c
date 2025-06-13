/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:54:25 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/23 12:37:17 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	char	*target;
	int		i;

	i = 0;
	target = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
		{
			target = (char *)&str[i];
		}
		i++;
	}
	if (c == '\0')
		return ((char *)(str + i));
	return (target);
}
