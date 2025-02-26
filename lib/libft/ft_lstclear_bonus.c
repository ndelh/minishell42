/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:41:54 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/15 17:41:22 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if ((!lst) || (!del))
		return ;
	while (*lst)
	{
		temp = *lst;
		del(temp->content);
		*lst = (temp->next);
		free(temp);
	}
	*lst = NULL;
}
