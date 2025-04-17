/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:11:41 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:25:50 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	is_redir_ender(char c)
{
	if (is_white_space(c))
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	count_inside_quote(t_line **line)
{
	t_line	*stoppage;
	int		count;

	count = 0;
	stoppage = (*line)->end_quote;
	*line = (*line)->next;
	while (*line != stoppage)
	{
		count++;
		(*line)->wr = 1;
		*line = (*line)->next;
	}
	*line = (*line)->next;
	return (count);
}

t_line	*add_quote_content(t_line *line, char *to_ret, int *i)
{
	t_line	*stoppage;

	stoppage = line->end_quote;
	while (line != stoppage->next)
	{
		if (line->wr)
			to_ret[(*i)++] = line->letter;
		line = line->next;
	}
	return (stoppage);
}

t_line	*go_to_last_node(t_line *line)
{
	while (line->next)
		line = line->next;
	return (line);
}
