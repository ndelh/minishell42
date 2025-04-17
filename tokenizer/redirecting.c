/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:20:36 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:24:58 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_redir(t_line *list)
{
	if (list->next && list->letter == list->next->letter)
		list = list->next->next;
	else
		list = list->next;
	while (list && is_white_space(list->letter))
		list = list->next;
	if (!list || is_redir_ender(list->letter))
	{
		ft_putendl_fd("incomplete redirection", 2);
		return (0);
	}
	return (1);
}

int	attribute_redir_type(t_line *list)
{
	if (list->letter == '<')
	{
		if (list->next->letter == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	if (list->next->letter == '>')
		return (APPEND);
	else
		return (OUTFILE);
}

void	complete_redir(t_line **list, int type)
{
	t_line	*reminder;

	reminder = *list;
	reminder->redir_type = type;
	*list = (*list)->next;
	if ((*list)->previous->letter == (*list)->letter)
		*list = (*list)->next;
	while (is_white_space((*list)->letter))
		*list = (*list)->next;
	while (1)
	{
		if ((*list)->type == S_QUOTE || (*list)->type == D_QUOTE)
			*list = (*list)->end_quote;
		if (!(*list)->next || (*list)->cmd_number != (*list)->next->cmd_number
			|| is_redir_ender((*list)->next->letter))
			break ;
		*list = (*list)->next;
	}
	reminder->end_redir = *list;
}

int	redirecting(t_line *list)
{
	int	type;

	while (list)
	{
		if (list->type == 0 && (list->letter == '<' || list->letter == '>'))
		{
			if (!parse_redir(list))
				return (0);
			type = attribute_redir_type(list);
			complete_redir(&list, type);
		}
		if (list)
			list = list->next;
	}
	return (1);
}
