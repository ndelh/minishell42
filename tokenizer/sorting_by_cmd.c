/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_by_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:14:21 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:11:47 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_last_in_redir(t_line **list, t_line *new)
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

void	add_last_cmd(t_cmd **list, t_cmd *new)
{
	static t_cmd	*cursor;

	if (!*list)
		*list = new;
	else
	{
		cursor->next = new;
		new->previous = cursor;
	}
	cursor = new;
}

t_cmd	*gen_cmd_node(void)
{
	t_cmd	*to_ret;

	to_ret = malloc(sizeof(t_cmd) * 1);
	if (!to_ret)
		return (NULL);
	ft_memset(to_ret, 0, sizeof(t_cmd));
	return (to_ret);
}

t_cmd	*sorting_by_cmd(t_line *line)
{
	int		nb;
	t_cmd	*cmd_list;
	t_cmd	*cmd_node;

	cmd_list = NULL;
	nb = 0;
	while (line)
	{
		nb++;
		cmd_node = gen_cmd_node();
		cmd_node->cmd_line = line;
		add_last_cmd(&cmd_list, cmd_node);
		while (line && line->cmd_number == nb)
			line = line->next;
		if (line)
		{
			line->previous->next = NULL;
			line->previous = NULL;
		}
	}
	return (cmd_list);
}
