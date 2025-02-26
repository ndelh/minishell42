/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:07:46 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/15 21:10:56 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*n_list;

	if (!lst || !f || !del)
		return (0);
	n_list = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&n_list, del);
			return (0);
		}
		ft_lstadd_back(&n_list, node);
		lst = lst->next;
	}
	return (n_list);
}
