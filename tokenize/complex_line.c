/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:09:31 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/22 18:45:48 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	global_len(t_token *list, t_token *stoppage)
{
	int	count;

	count = 0;
	while (list != stoppage)
	{
		count += ft_strlen(list->piece);
		list = list->next;
	}
	return (count);
}

void	one_complex_line(t_token **list, t_cmd *cmd, int *i)
{
	t_token	*stoppage;
	int		len;

	stoppage = (*list)->block_end->next;
	len = (global_len(*list, stoppage) + 1);
	cmd->cmd_arg[*i] = ft_calloc(1, len);
	while (1)
	{
		ft_strlcat(cmd->cmd_arg[*i], (*list)->piece, len);
		if ((*list)->next == stoppage)
			break ;
		*list = (*list)->next;
	}
	(*i)++;
}

void	multiple_complex_line(t_token *list, t_cmd *cmd, int *i)
{
	int		j;
	char	**split_space;

	j = 0;
	split_space = split_w_space(list->piece);
	while (split_space[j])
	{
		cmd->cmd_arg[*i] = split_space[j];
		(*i)++;
		j++;
	}
	free(split_space[j]);
	free(split_space);
}
