/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:41:58 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/17 16:39:28 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dubious_redir(t_data *data)
{
	if (data->no_exec)
		return ;
	data->no_exec = 1;
	ft_putendl_fd("error : ambiguous redirect", 2);
}

void	check_h_doc(t_token *node, t_line *list)
{
	if (node->type != HEREDOC)
		return ;
	while (list)
	{
		if (list->end_quote)
			break ;
		list = list->next;
	}
	if (list)
		node->h_no_expand = 1;
}

void	write_in_hdoc(t_line *list, int fd)
{
	while (list)
	{
		ft_putchar_fd(list->letter, fd);
		list = list->next;
	}
	ft_putchar_fd('\n', fd);
}
