/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:45:36 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/17 15:01:58 by ndelhota         ###   ########.fr       */
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

char	*gen_tab_line(t_line **line, char **tab, t_data *data)
{
	char	*to_ret;
	int		i;

	i = count_char_line(*line);
	to_ret = ft_calloc(sizeof(char), (i + 1));
	if (!to_ret)
	{
		ft_free_tab(tab);
		mns_exit(data, NULL);
	}
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

char	**create_cmd_tab(t_line *line, t_data *data)
{
	char	**tab;
	int		i;

	i = count_line(line);
	tab = ft_calloc(sizeof(char *), (i + 1));
	if (!tab)
		mns_exit(data, NULL);
	tab[i] = NULL;
	i = 0;
	while (line)
	{
		while (line && is_white_space(line->letter))
			line = line->next;
		if (line)
		{
			tab[i++] = gen_tab_line(&line, tab, data);
		}
	}
	return (tab);
}

void	convert_cmd(t_cmd *list, t_data *data)
{
	while (list)
	{
		list->cmd_arg = create_cmd_tab(list->cmd_line, data);
		free_line_list(&list->cmd_line);
		list = list->next;
	}
}
