/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:53 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 14:10:09 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	convert_cmd_list(data->cmd_list);
	convert_redir_list(data->cmd_list);
}
