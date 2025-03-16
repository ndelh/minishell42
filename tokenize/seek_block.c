/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:46:21 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:16:49 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_next_list(t_token *list)
{
	if (list->type == UNKNOW && ft_strchr(list->piece, ' '))
		return (0);
	if (list->next->type == REDIR)
		return (0);
	if (*(list->next->piece) == ' ')
		return (0);
	return (1);
}

t_token	*seek_end_of_block(t_token *list)
{
	t_token	*found;

	found = NULL;
	while (list->next && go_next_list(list))
	{
		list = list->next;
		found = list;
	}
	if (found && ft_strchr(found->piece, ' '))
		arrange_tail(&found, found->previous, found->next);
	return (found);
}

void	gen_blocklist(t_token **cursor, t_token *old_p, t_token *old_n)
{
	t_token	*head;

	head = arrange_head(*cursor, old_p, old_n);
	if (head)
		*cursor = head;
	head = seek_end_of_block(*cursor);
	if (head)
		(*cursor)->block_end = head;
}

void	adjust_blocklist(t_token **list)
{
	t_token	*cursor;
	t_token	*remind_p;
	t_token	*remind_n;

	cursor = *list;
	while (cursor)
	{
		if (cursor->type == D_QUOTE || cursor->type == S_QUOTE
			|| is_incomplete(cursor->piece)
			|| (cursor->type == REDIR && redir_alone(cursor->piece)))
		{
			remind_p = cursor->previous;
			remind_n = cursor->next;
			gen_blocklist(&cursor, remind_p, remind_n);
			if (!remind_p)
				*list = cursor;
			if (cursor->block_end)
				cursor = cursor->block_end;
		}
		cursor = cursor->next;
	}
}

void	seek_block(t_cmd *cmd_list)
{
	while (cmd_list)
	{
		adjust_blocklist(&cmd_list->current_cmd);
		cmd_list = cmd_list->next;
	}
}
