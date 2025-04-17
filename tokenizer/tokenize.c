/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:06:49 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/17 14:39:44 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize(char *line, t_data *data)
{
	t_line	*list;

	list = gen_list(line, data);
	if (!quoting(list))
		free_line_list(&list);
	if (!piping(list, line))
		free_line_list(&list);
	if (!redirecting(list))
		free_line_list(&list);
	if (!list)
		data->exit = 2;
	data->cmd_list = sorting_by_cmd(list);
	sorting_in_cmd(data->cmd_list);
	gen_expand(data, data->cmd_list);
	create_redir_list(data->cmd_list, data);
	convert_cmd(data->cmd_list);
	is_builtin(data->cmd_list);
	change_hdoc(data->cmd_list, data);
}
