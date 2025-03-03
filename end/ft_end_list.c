/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:48:40 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/02 14:44:30 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token *to_free)
{
	t_token	*temp;

	while (to_free)
	{
		temp = to_free->next;
		printf("%s\n", to_free->piece);
		printf("%u\n", to_free->cmd_num);
		free(to_free->piece);
		free(to_free);
		to_free = temp;
	}
}
