/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:19:03 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/17 14:38:31 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_last_line(t_line **line, t_line *new_one)
{
	static t_line	*cursor;

	if (!*line)
		*line = new_one;
	else
	{
		cursor->next = new_one;
		new_one->previous = cursor;
	}
	cursor = new_one;
	cursor->next = NULL;
}

t_line	*gen_node(char line)
{
	t_line	*to_ret;

	to_ret = malloc(sizeof(t_line) * 1);
	if (!to_ret)
		return (NULL);
	ft_memset(to_ret, 0, sizeof(t_line));
	to_ret->letter = line;
	return (to_ret);
}

t_line	*gen_list(char *line, t_data *data)
{
	t_line	*to_ret;
	t_line	*to_add;

	to_ret = NULL;
	while (*line)
	{
		to_add = gen_node(*line);
		if (!to_add)
		{
			free_line_list(&to_ret);
			mns_exit(data, NULL);
		}
		add_last_line(&to_ret, to_add);
		line++;
	}
	return (to_ret);
}
