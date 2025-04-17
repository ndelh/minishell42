/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:11:08 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:23:07 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_last_node(t_token **list, t_token *new)
{
	static t_token	*cursor;

	if (!*list)
		*list = new;
	else
	{
		cursor->next = new;
		new->previous = cursor;
	}
	cursor = new;
}

int	count_char_redir(t_line *line, t_data *data)
{
	int	count;

	count = 0;
	if (line->redir_type == HEREDOC || line->redir_type == APPEND)
		line = line->next->next;
	else
		line = line->next;
	while (line && is_white_space(line->letter))
		line = line->next;
	while (line)
	{
		if (is_white_space(line->letter))
			dubious_redir(data);
		if (line->end_quote)
			count += count_inside_quote(&line);
		else
		{
			count++;
			line->wr = 1;
			line = line->next;
		}
	}
	return (count);
}

void	fill_redir_node(t_token *node, t_line **line, t_data *data)
{
	int		i;
	t_line	*stoppage;
	t_line	*temp;
	char	*to_fill;

	stoppage = (*line)->end_redir->next;
	if (stoppage)
		stoppage->previous = NULL;
	(*line)->end_redir->next = NULL;
	*line = expand_in_redir(data, *line);
	i = count_char_redir(*line, data);
	node->type = (*line)->redir_type;
	to_fill = ft_calloc(sizeof(char), (i + 1));
	i = 0;
	temp = *line;
	while (*line)
	{
		if ((*line)->wr)
			to_fill[i++] = (*line)->letter;
		*line = (*line)->next;
	}
	free_line_list(&temp);
	node->piece = to_fill;
	*line = stoppage;
}

t_token	*convert_redir_list(t_line *line, t_data *data)
{
	t_token	*list;
	t_token	*to_add;

	list = NULL;
	while (line)
	{
		to_add = malloc(sizeof(t_token) * 1);
		ft_memset(to_add, 0, sizeof(t_token));
		fill_redir_node(to_add, &line, data);
		add_last_node(&list, to_add);
	}
	return (list);
}

void	create_redir_list(t_cmd *list, t_data *data)
{
	while (list)
	{
		list->rdir_list = convert_redir_list(list->redir_line, data);
		list->redir_line = NULL;
		list = list->next;
	}
}
