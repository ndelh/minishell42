/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_block_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:04:35 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:13:33 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**shatter_end(char *s)
{
	char	*cursor;
	char	**to_ret;

	to_ret = malloc(sizeof(char *) * 2);
	cursor = s;
	while (*cursor == ' ')
		cursor++;
	while (*cursor != ' ')
		cursor++;
	to_ret[0] = ft_substr(s, 0, ft_strlen(s)- ft_strlen(cursor));
	to_ret[1] = ft_substr(cursor, 0, ft_strlen(cursor));
	return (to_ret);
}

t_token	*fracture_tail(t_token *to_frac)
{
	t_token	*node_a;
	t_token	*node_b;
	char	**shattered;

	shattered = shatter_end(to_frac->piece);
	node_a = malloc(sizeof(t_token));
	node_b = malloc(sizeof(t_token));
	ft_memset(node_a, 0, sizeof(t_token));
	ft_memset(node_b, 0, sizeof (t_token));
	node_a->piece = *shattered;
	node_b->piece = shattered[1];
	free(shattered);
	node_a->next = node_b;
	node_b->previous = node_a;
	return (node_a);
}

void	arrange_tail(t_token **cursor, t_token *old_p, t_token *old_n)
{
	t_token	*modify;

	modify = *cursor;
	if (ft_strchr(modify->piece, ' ') && modify->type == UNKNOW)
	{
		modify = fracture_tail(modify);
		modify->previous = old_p;
		modify->next->next = old_n;
		if (old_n)
			old_n->previous = modify->next;
		if (old_p)
			old_p->next = modify;
		free((*cursor)->piece);
		free(*cursor);
		*cursor = modify;
	}
}
