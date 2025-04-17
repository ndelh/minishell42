/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:16:45 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:25:12 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **to_free)
{
	char	**reminder;

	reminder = to_free;
	while (*to_free)
	{
		printf("%s\n", *to_free);
		free(*to_free);
		to_free++;
	}
	free(reminder);
}

void	free_line_list(t_line **line)
{
	t_line	*temp;

	if (!*line)
		return ;
	while (*line)
	{
		temp = (*line)->next;
		free(*line);
		*line = temp;
	}
	*line = NULL;
}
