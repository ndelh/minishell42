/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:53 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/03 15:10:56 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd_number(t_token *list)
{
	int	num;

	num = 1;
	while (list)
	{
		if (*list->piece == '|')
			num++;
		list->cmd_num = num;
		list = list->next;
	}
}

void	ft_tokenize(t_data *data, char *line)
{
	char	**first_split;

	first_split = split_quote(line);
	first_sort(data, first_split);
	gen_pipe_list(&data->token_list);
	add_cmd_number(data->token_list);
	gen_redirection_line(&data->token_list);
	free_token_list(data->token_list);
	data->token_list = NULL;
}
