/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:53:24 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:14:04 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_last_cmd(t_cmd **list, t_cmd *to_add)
{
	static t_cmd	*cursor;

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

t_cmd	*create_cmd_node(t_token *to_shatter)
{
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof(t_cmd));
	ft_memset(cmd_list, 0, sizeof(t_cmd));
	cmd_list->current_cmd = to_shatter;
	return (cmd_list);
}

void	remove_pipe(t_token *node)
{
	char	*temp;

	temp = ft_substr(node->piece, 1, ft_strlen(node->piece) - 1);
	free(node->piece);
	node->piece = temp;
}

void	create_cmd_list(t_data *data, t_token *to_shatter)
{
	t_cmd	*to_add;

	to_add = create_cmd_node(to_shatter);
	ft_add_last_cmd(&data->cmd_list, to_add);
	while (to_shatter)
	{
		if (*(to_shatter->piece) == '|')
		{
			to_shatter->previous->next = NULL;
			to_shatter->previous = NULL;
			remove_pipe(to_shatter);
			to_add = create_cmd_node(to_shatter);
			ft_add_last_cmd(&data->cmd_list, to_add);
		}
		to_shatter = to_shatter->next;
	}
	data->token_list = NULL;
}
