/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_block_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:51:41 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:05:51 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_alone(char *s)
{
	while (*s == 32)
		s++;
	if (*s == '<' || *s == '>')
		s++;
	if (*s == '<' || *s == '>')
		s++;
	while (*s == 32)
		s++;
	if (*s)
		return (0);
	return (1);
}

int	is_incomplete(char *s)
{
	if (!s || !*s)
		return (0);
	while (*s)
		s++;
	if (*(s - 1) != ' ')
		return (1);
	else
		return (0);
}

char	**shatter_incomplete_start(char *s)
{
	char	*cursor;
	char	**to_ret;

	to_ret = malloc(sizeof(char *) * 2);
	cursor = s;
	while (*cursor)
		cursor++;
	while (*(cursor - 1) != ' ')
		cursor--;
	to_ret[0] = ft_substr(s, 0, ft_strlen(s)- ft_strlen(cursor));
	to_ret[1] = ft_substr(cursor, 0, ft_strlen(cursor));
	return (to_ret);
}

t_token	*fracture_incomplete_head(t_token *to_frac)
{
	t_token	*node_a;
	t_token	*node_b;
	char	**shattered;

	shattered = shatter_incomplete_start(to_frac->piece);
	node_a = malloc(sizeof(t_token));
	node_b = malloc(sizeof(t_token));
	ft_memset(node_a, 0, sizeof(t_token));
	ft_memset(node_b, 0, sizeof(t_token));
	node_a->piece = *shattered;
	node_b->piece = shattered[1];
	node_a->next = node_b;
	node_b->previous = node_a;
	free(shattered);
	return (node_a);
}

t_token	*arrange_head(t_token *head, t_token *old_p, t_token *old_n)
{
	t_token	*to_ret;

	if (head->type != UNKNOW || !ft_strchr(head->piece, ' '))
		return (NULL);
	to_ret = fracture_incomplete_head(head);
	free(head->piece);
	free(head);
	to_ret->previous = old_p;
	to_ret->next->next = old_n;
	if (old_p)
		old_p->next = to_ret;
	if (old_n)
		old_n->previous = to_ret->next;
	return (to_ret);
}
