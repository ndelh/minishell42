/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_in_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:17:14 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:17:26 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_last_in_word(t_line **list, t_line *new)
{
	static t_line	*cursor;

	if (!*list)
		*list = new;
	else
	{
		cursor->next = new;
		new->previous = cursor;
	}
	cursor = new;
}

void	redir_add(t_line **to_split, t_cmd *cmd)
{
	t_line	*stoppage;
	t_line	*to_ret;

	stoppage = (*to_split)->end_redir;
	to_ret = (*to_split)->end_redir->next;
	if ((*to_split)->previous)
		(*to_split)->previous->next = NULL;
	(*to_split)->previous = NULL;
	stoppage->next = NULL;
	while (*to_split)
	{
		add_last_in_redir(&cmd->redir_line, *to_split);
		*to_split = (*to_split)->next;
	}
	*to_split = to_ret;
}

void	sort_between_two(t_line *to_split, t_cmd *list)
{
	while (to_split)
	{
		if (!to_split->end_redir)
		{
			add_last_in_word(&list->cmd_line, to_split);
			to_split = to_split->next;
		}
		else
		{
			redir_add(&to_split, list);
			if (to_split)
				to_split->previous = NULL;
		}
	}
}

void	process_sort(t_cmd *list)
{
	t_line	*to_tear;

	to_tear = list->cmd_line;
	list->cmd_line = NULL;
	sort_between_two(to_tear, list);
}

void	sorting_in_cmd(t_cmd *list)
{
	while (list)
	{
		process_sort(list);
		list = list->next;
	}
}
