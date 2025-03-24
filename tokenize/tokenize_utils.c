/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:54:49 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/24 12:23:37 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_not_needed(t_token *list)
{
	t_token	*stoppage;
	t_token	*cursor;

	cursor = list;
	stoppage = list->block_end->next;
	while (cursor != stoppage)
	{
		if (cursor->type == S_QUOTE || cursor->type == D_QUOTE)
		{
			list->h_no_expand = 1;
			break ;
		}
		cursor = cursor->next;
	}
}

char	*sanitize(char *s)
{
	char	*end;
	char	*to_ret;

	while (*s && (is_space(*s) || *s == '<' || *s == '>'))
		s++;
	end = s;
	while (*(end))
		end++;
	while (is_space(*(end - 1)))
		end--;
	to_ret = ft_substr(s, 0, ft_strlen(s) - ft_strlen(end));
	return (to_ret);
}
