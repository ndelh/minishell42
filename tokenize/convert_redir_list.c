/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:50:26 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/23 18:42:25 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stitch_piece(t_token *node, t_token *list, int i)
{
	t_token	*stoppage;
	t_token	*temp;

	stoppage = list->block_end->next;
	while (list != stoppage)
	{
		ft_strlcat(node->piece, list->piece, i);
		free(list->piece);
		temp = list->next;
		free(list);
		list = temp;
	}
}

void	ft_relink(t_token *to_ret, t_token *target)
{
	to_ret->previous = target->previous;
	if (target->previous)
		target->previous->next = to_ret;
	target = target->block_end->next;
	to_ret->next = target;
	if (target)
		target->previous = to_ret;
}

t_token	*merge_block(t_token *list)
{
	t_token	*to_ret;
	int		i;

	to_ret = malloc(sizeof(t_token));
	ft_memset(to_ret, 0, sizeof(t_token));
	to_ret->type = list->type;
	to_ret->h_no_expand = list->h_no_expand;
	ft_relink(to_ret, list);
	i = global_len(list, list->block_end->next) + 1;
	to_ret->piece = ft_calloc(1, i);
	stitch_piece(to_ret, list, i);
	return (to_ret);
}

void	reassemble_redir(t_token **list)
{
	t_token	*new_node;
	t_token	*cursor;

	cursor = *list;
	while (cursor)
	{
		if (cursor->block_end)
		{
			if (cursor->type == HEREDOC)
				expand_not_needed(cursor);
			new_node = merge_block(cursor);
			if (!new_node->previous)
				*list = new_node;
			cursor = new_node;
		}
		cursor = cursor->next;
	}
}

void	convert_redir_list(t_cmd *list)
{
	while (list)
	{
		reassemble_redir(&list->rdir_list);
		list = list->next;
	}
}
