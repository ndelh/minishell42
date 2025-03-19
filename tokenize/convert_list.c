/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:12:55 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/19 16:22:35 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_count(char *s)
{
	int	count;

	count = 0;
	if (!s || !*s)
		return (0);
	if (*s == '|')
		s++;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s && *s != ' ')
			count++;
		while (*s && *s != ' ')
			s++;
	}
	return (count);
}

int	line_needed(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->block_end)
		{
			list = list->block_end;
			i++;
		}
		else if (list->type == D_QUOTE || list->type == S_QUOTE
			|| !ft_strchr(list->piece, ' '))
			i++;
		else
			i += split_count(list->piece);
		list = list->next;
	}
	return (i);
}

void	gen_cmd_tab(t_cmd *cmd, t_token *list)
{
	int	i;

	cmd->tab_line = line_needed(list);
	if (!cmd->tab_line)
		return ;
	cmd->cmd_arg = malloc(sizeof(char *) * (cmd->tab_line + 1));
	i = 0;
	while (list)
	{
		if (list->block_end)
			one_complex_line(&list, cmd, &i);
		else if (list->type == D_QUOTE || list->type == S_QUOTE
			|| !ft_strchr(list->piece, ' '))
		{
			cmd->cmd_arg[i] = ft_strdup(list->piece);
			i++;
		}
		else
			multiple_complex_line(list, cmd, &i);
		if (list)
			list = list->next;
	}
	cmd->cmd_arg[i] = NULL;
}

void	adjust_cmd(t_token **list)
{
	t_token	*temp;

	if (!list || !*list)
		return ;
	if ((*list)->type == PIPE && *(*list)->piece == 0)
	{
		temp = (*list)->next;
		free((*list)->piece);
		free(*list);
		*list = temp;
		if (*list)
			(*list)->previous = NULL;
	}
}

void	convert_cmd_list(t_cmd *cmd)
{
	while (cmd)
	{
		adjust_cmd(&cmd->current_cmd);
		gen_cmd_tab(cmd, cmd->current_cmd);
		cmd = cmd->next;
	}
}
