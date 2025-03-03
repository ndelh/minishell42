/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:54:00 by ndelhota          #+#    #+#             */
/*   Updated: 2025/02/27 15:40:18 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_last(t_token **list, t_token *to_add)
{
	static t_token	*cursor;

	if (!*list || !list)
	{
		*list = to_add;
	}
	else
	{
		cursor->next = to_add;
		to_add->previous = cursor;
	}
	cursor = to_add;
}

void	ft_insert(t_data *data, char *s)
{
	t_token	*to_insert;

	to_insert = malloc(sizeof(t_token));
	if (!to_insert)
	{
		free(s);
		return ;
	}
	ft_memset(to_insert, 0, sizeof(t_token));
	to_insert->piece = s;
	if (*s == '\'')
		to_insert->type = S_QUOTE;
	if (*s == '\"')
		to_insert->type = D_QUOTE;
	ft_add_last(&data->token_list, to_insert);
}

void	first_sort(t_data *data, char **first_split)
{
	char	**to_free;

	to_free = first_split;
	while (*first_split)
	{
		ft_insert(data, *first_split);
		first_split++;
	}
	free(*first_split);
	free(to_free);
}
