/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:18:24 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/22 18:09:48 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_create_insert(char *pipe)
{
	t_token	*to_insert;

	to_insert = malloc(sizeof(t_token));
	ft_memset(to_insert, 0, sizeof(t_token));
	to_insert->piece = pipe;
	return (to_insert);
}

void	gen_new_chain(t_token **list, char **tab)
{
	t_token	*to_insert;
	t_token	*new_list;
	char	**to_free;

	to_free = tab;
	new_list = NULL;
	while (*tab)
	{
		to_insert = ft_create_insert(*tab);
		ft_add_last(&new_list, to_insert);
		tab++;
	}
	free(*tab);
	free(to_free);
	*list = new_list;
}

void	split_pipe(t_token **to_frag)
{
	t_token	*new_list;
	char	**frag_result;

	frag_result = split_at_char((*to_frag)->piece, '|');
	new_list = NULL;
	gen_new_chain(&new_list, frag_result);
	free((*to_frag)->piece);
	free(*to_frag);
	*to_frag = new_list;
}

void	restablish_link(t_token **cursor, t_token *p, t_token *n)
{
	if (p)
	{
		(*cursor)->previous = p;
		p->next = *cursor;
	}
	while ((*cursor)->next)
		*cursor = (*cursor)->next;
	if (n)
	{
		n->previous = *cursor;
		(*cursor)->next = n;
	}
	*cursor = n;
}

void	gen_pipe_list(t_token **old_list)
{
	t_token	*cursor;
	t_token	*remind_p;
	t_token	*remind_n;

	cursor = (*old_list);
	while (cursor)
	{
		if (cursor->type != UNKNOW || !ft_strchr(cursor->piece, '|'))
			cursor = cursor->next;
		else
		{
			remind_p = cursor->previous;
			remind_n = cursor->next;
			split_pipe(&cursor);
			if (!remind_p)
				*old_list = cursor;
			restablish_link(&cursor, remind_p, remind_n);
		}
	}
}
