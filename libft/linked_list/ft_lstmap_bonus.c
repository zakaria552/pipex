/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:37:46 by zfarah            #+#    #+#             */
/*   Updated: 2025/04/28 09:06:49 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*mapped_tmp;

	if (!lst)
		return (NULL);
	mapped = malloc(sizeof(t_list));
	if (!mapped)
		return (NULL);
	mapped_tmp = mapped;
	while (lst->next)
	{
		mapped_tmp->content = f(lst->content);
		mapped_tmp->next = malloc(sizeof(t_list));
		if (!mapped_tmp->next)
		{
			ft_lstclear(&mapped, del);
			return (NULL);
		}
		mapped_tmp = mapped_tmp->next;
		lst = lst->next;
	}
	mapped_tmp->content = f(lst->content);
	mapped_tmp->next = NULL;
	return (mapped);
}
