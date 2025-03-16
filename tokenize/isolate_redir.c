/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:51:46 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:12:00 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_last_special(t_token **list, t_token *to_add)
{
	static t_token	*cursor;

	if (!list || !*list)
		*list = to_add;
	else
	{
		cursor->next = to_add;
		to_add->previous = cursor;
	}
	while (to_add->next)
		to_add = to_add->next;
	cursor = to_add;
}

t_token	*move_redir(t_token **cursor)
{
	t_token	*prev_redir;
	t_token	*to_move;

	prev_redir = (*cursor)->previous;
	to_move = *cursor;
	if ((*cursor)->block_end)
		*cursor = (*cursor)->block_end->next;
	else
		*cursor = (*cursor)->next;
	if (*cursor)
	{
		(*cursor)->previous->next = NULL;
		(*cursor)->previous = prev_redir;
	}
	if (prev_redir)
		prev_redir->next = *cursor;
	to_move->previous = NULL;
	return (to_move);
}

void	isolate_redir(t_cmd *cmd)
{
	t_token	*cursor;
	t_token	*to_add;
	t_token	*before_rdir;

	cursor = cmd->current_cmd;
	while (cursor)
	{
		if (cursor->type == REDIR)
		{
			before_rdir = cursor->previous;
			to_add = move_redir(&cursor);
			ft_add_last_special(&cmd->rdir_list, to_add);
			if (!before_rdir)
				cmd->current_cmd = cursor;
		}
		else
			cursor = cursor->next;
	}
}

void	sort_redir_exe(t_cmd *list)
{
	while (list)
	{
		isolate_redir(list);
		list = list->next;
	}
}
