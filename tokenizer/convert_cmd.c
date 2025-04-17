/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:45:36 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:12:40 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_line(t_line *line)
{
	int	count;

	count = 0;
	while (line)
	{
		while (line && is_white_space(line->letter))
			line = line->next;
		if (line)
			count++;
		while (line && !is_white_space(line->letter))
		{
			if (line->end_quote)
				line = line->end_quote->next;
			else
				line = line->next;
		}
	}
	return (count);
}

int	count_char_line(t_line *line)
{
	int	count;

	count = 0;
	while (line && !is_white_space(line->letter))
	{
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

char	*gen_tab_line(t_line **line)
{
	char	*to_ret;
	int		i;

	i = count_char_line(*line);
	to_ret = ft_calloc(sizeof(char), (i + 1));
	if (!to_ret)
		return (NULL);
	i = 0;
	while (*line && !is_white_space((*line)->letter))
	{
		if ((*line)->wr)
			to_ret[i++] = (*line)->letter;
		else
			*line = add_quote_content(*line, to_ret, &i);
		*line = (*line)->next;
	}
	return (to_ret);
}

char	**create_cmd_tab(t_line *line)
{
	char	**tab;
	int		i;

	i = count_line(line);
	tab = malloc(sizeof(char *) * (i + 1));
	tab[i] = NULL;
	i = 0;
	while (line)
	{
		while (line && is_white_space(line->letter))
			line = line->next;
		if (line)
		{
			tab[i++] = gen_tab_line(&line);
		}
	}
	return (tab);
}

void	convert_cmd(t_cmd *list)
{
	while (list)
	{
		list->cmd_arg = create_cmd_tab(list->cmd_line);
		free_line_list(&list->cmd_line);
		list = list->next;
	}
}
