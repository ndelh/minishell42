/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:01:14 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:13:45 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	s_quoting(t_line **line)
{
	t_line	*reminder;

	reminder = *line;
	reminder->type = S_QUOTE;
	*line = (*line)->next;
	while (*line && (*line)->letter != '\'')
	{
		(*line)->type = S_QUOTE;
		*line = (*line)->next;
	}
	if (*line)
	{
		reminder->end_quote = *line;
		(*line)->type = S_QUOTE;
	}
}

void	d_quoting(t_line **line)
{
	t_line	*reminder;

	reminder = *line;
	reminder->type = D_QUOTE;
	*line = (*line)->next;
	while (*line && (*line)->letter != '\"')
	{
		(*line)->type = D_QUOTE;
		*line = (*line)->next;
	}
	if (*line)
	{
		reminder->end_quote = *line;
		(*line)->type = D_QUOTE;
	}
}

int	quoting(t_line *line)
{
	while (line)
	{
		if (line->letter == '\'')
			s_quoting(&line);
		else if (line->letter == '\"')
			d_quoting(&line);
		if (!line)
		{
			ft_putendl_fd("syntax error : unclosed quote", 2);
			return (0);
		}
		line = line->next;
	}
	return (1);
}
