/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:30:23 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/18 12:27:08 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_double_pipe(char *line)
{
	char	a;

	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			a = *line;
			line++;
			while (*line && *line != a)
				line++;
		}
		if (*line && *line == '|' && *(line + 1) == '|')
			return (0);
		line++;
	}
	return (1);
}

int	parse_pipe(char *line)
{
	while (*line && is_white_space(*line))
		line++;
	if (*line == '|')
		return (0);
	while (*line && *(line + 1))
		line++;
	while (is_white_space(*line))
		line--;
	if (*line == '|')
		return (0);
	return (1);
}

void	attribute_cmd_number(t_line *list)
{
	int		numb;
	t_line	*to_free;

	numb = 1;
	while (list)
	{
		if (list->type == 0 && list->letter == '|')
		{
			to_free = list;
			list->next->previous = list->previous;
			list = list->previous;
			list->next = to_free->next;
			free(to_free);
			numb++;
		}
		else
			list->cmd_number = numb;
		list = list->next;
	}
}

int	piping(t_line *list, char *line)
{
	if (!list)
		return (0);
	if (!parse_pipe(line) || !check_double_pipe(line))
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (0);
	}
	attribute_cmd_number(list);
	return (1);
}
