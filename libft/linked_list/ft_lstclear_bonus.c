/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:10:03 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:04:08 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*to_del;

	current = *lst;
	if (!current)
		return ;
	while (current->next)
	{
		to_del = current;
		current = current->next;
		del(to_del->content);
		free(to_del);
	}
	del(current->content);
	free(current);
	*lst = NULL;
}
