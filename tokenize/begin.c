/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:53 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/29 14:46:32 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_return_rl(t_data *data)
{
	free_cmd_list(data->cmd_list);
	data->cmd_list = NULL;
	g_signal = 0;
	data->exit = 130;
}

void	ft_tokenize(t_data *data, char *line)
{
	char	**first_split;

	first_split = split_quote(line);
	first_sort(data, first_split);
	gen_pipe_list(&data->token_list);
	gen_redirection_line(&data->token_list);
	create_cmd_list(data, data->token_list);
	seek_block(data->cmd_list);
	sort_redir_exe(data->cmd_list);
	expand_in_list(data->cmd_list, data);
	convert_cmd_list(data->cmd_list, data);
	is_builtin(data->cmd_list);
	convert_redir_list(data->cmd_list);
	change_hdoc(data->cmd_list, data);
	if (g_signal == SIGINT)
		ft_return_rl(data);
}
