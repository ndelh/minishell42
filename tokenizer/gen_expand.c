/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:28:52 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:24:39 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	existing_new(t_line **cursor, t_line **cmd_line,
		t_line *end_expand, t_line *new)
{
	t_line	*to_free;

	to_free = *cursor;
	if (!(*cursor)->previous)
		*cmd_line = new;
	else
	{
		(*cursor)->previous->next = new;
		new->previous = (*cursor)->previous;
	}
	new = go_to_last_node(new);
	if (end_expand->next)
	{
		end_expand->next->previous = new;
		new->next = end_expand->next;
	}
	to_free->end_expand->next = NULL;
	free_line_list(&to_free);
	*cursor = new->next;
}

void	empty_new(t_line **cursor, t_line **cmd_line, t_line *end_expand)
{
	t_line	*to_free;

	to_free = *cursor;
	if (!(*cursor)->previous)
	{
		*cmd_line = end_expand->next;
		if (end_expand->next)
			end_expand->next->previous = NULL;
	}
	else
	{
		(*cursor)->previous->next = end_expand->next;
		if (end_expand->next)
			end_expand->next->previous = (*cursor)->previous;
	}
	*cursor = end_expand->next;
	to_free->end_expand->next = NULL;
	free_line_list(&to_free);
}

t_line	*create_cmd_expand(t_env *env, t_line *line)
{
	t_env	*to_exp;
	t_line	*to_ret;

	to_ret = NULL;
	to_exp = find_env_node(env, line);
	if (to_exp && to_exp->content)
		to_ret = gen_list(to_exp->content);
	return (to_ret);
}

void	expand_in_cmd(t_data *data, t_cmd *cmd)
{
	t_line	*new;
	t_line	*cursor;

	if (!seek_expand_end_cmd(cmd->cmd_line))
		return ;
	cursor = cmd->cmd_line;
	while (cursor)
	{
		if (cursor->end_expand)
		{
			new = create_cmd_expand(data->my_env, cursor);
			if (new)
				existing_new(&cursor, &cmd->cmd_line, cursor->end_expand,
					new);
			else
				empty_new(&cursor, &cmd->cmd_line, cursor->end_expand);
			if (cursor && !cursor->previous)
				cmd->cmd_line = cursor;
		}
		else
			cursor = cursor->next;
	}
}

void	gen_expand(t_data *data, t_cmd *cmd)
{
	while (cmd)
	{
		expand_in_cmd(data, cmd);
		cmd = cmd->next;
	}
}
