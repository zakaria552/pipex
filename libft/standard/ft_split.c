/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:39:46 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 11:51:30 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "standard.h"

static void	*free_matrix_mem(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

static int	get_words(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static int	str_split(char const *s, char c, char **words, int word_count)
{
	int		w;
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	w = 0;
	while (w < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i + size] && s[i + size] != c)
			size++;
		words[w] = malloc((size + 1) * sizeof(char));
		if (!words[w])
		{
			free_matrix_mem(words);
			return (0);
		}
		ft_strlcpy(words[w], s + (i + size - size), size + 1);
		i += size;
		size = 0;
		w++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		word_count;
	int		splitted;

	word_count = get_words(s, c);
	arr = malloc((word_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[word_count] = NULL;
	splitted = str_split(s, c, arr, word_count);
	if (!splitted)
		return (NULL);
	return (arr);
}
