/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:03 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 13:07:34 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_redir(char *s)
{
	while (*s && *s != '<' && *s != '>')
		s++;
	if (*s)
		return (1);
	else
		return (0);
}

void	split_rline(t_token **to_frag)
{
	t_token	*new_list;
	char	**frag_result;

	frag_result = split_at_redir((*to_frag)->piece);
	if (!frag_result)
		return ;
	new_list = NULL;
	gen_new_chain(&new_list, frag_result);
	if (!new_list)
		return ;
	free((*to_frag)->piece);
	free(*to_frag);
	*to_frag = new_list;
}

void	add_redir_type(t_token *cursor)
{
	while (cursor)
	{
		if (has_redir(cursor->piece))
			cursor->type = REDIR;
		cursor = cursor->next;
	}
}

void	gen_redirection_line(t_token **old_list)
{
	t_token	*cursor;
	t_token	*remind_p;
	t_token	*remind_n;

	cursor = *old_list;
	while (cursor)
	{
		if (cursor->type == UNKNOW && has_redir(cursor->piece))
		{
			remind_p = cursor->previous;
			remind_n = cursor->next;
			split_rline(&cursor);
			add_redir_type(cursor);
			if (!remind_p)
				*old_list = cursor;
			restablish_link(&cursor, remind_p, remind_n);
		}
		else
			cursor = cursor->next;
	}
}
