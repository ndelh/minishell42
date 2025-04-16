/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:37:23 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:59:19 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	seek_expand_end_redir(t_line *line)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line->type == S_QUOTE)
			line = line->end_quote->next;
		else if (line->redir_type == HEREDOC)
			line = line->end_redir->next;
		else if (line && (line->letter == '$'))
		{
			if (line->next && !is_white_space(line->next->letter))
			{
				find_end_expand(&line);
				i++;
			}
		}
		if (line)
			line = line->next;
	}
	return (i);
}

t_line	*expand_in_redir(t_data *data, t_line *redir)
{
	t_line	*cursor;
	t_line	*new;
	t_line	*head;

	head = redir;
	if (!seek_expand_end_redir(head))
		return (head);
	cursor = head;
	while (cursor)
	{
		if (cursor->end_expand)
		{
			new = create_cmd_expand(data->my_env, cursor, data);
			if (new)
				existing_new(&cursor, &head, cursor->end_expand, new);
			else
				empty_new(&cursor, &head, cursor->end_expand);
			if (cursor && !cursor->previous)
				head = cursor;
		}
		else
			cursor = cursor->next;
	}
	return (head);
}
