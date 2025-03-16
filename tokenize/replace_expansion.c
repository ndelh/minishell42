/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:33:37 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:09:44 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	has_expand(char *s)
{
	while (*s && *s != '$')
		s++;
	if (*s)
		return (1);
	return (0);
}

void	replace_expansion(t_data *data, t_token *list)
{
	while (*list)
	{
		list = list->next;
		if (list->type != S_QUOTE && has_expand(list->piece))
			remodulate_list(list);
	}
}
