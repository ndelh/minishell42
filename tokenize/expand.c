/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:29:38 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/24 13:38:12 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gen_expand_line(char *s, t_env *env, t_token *list)
{
	char	**to_join;
	char	*to_ret;
	int		i;

	if (!env)
		return (NULL);
	i = count_expand_split(s);
	to_join = isolate_expand(s, i);
	if (!to_join)
		return (NULL);
	replace_expand(to_join, env, list);
	to_ret = ft_mend_line(to_join, i);
	free_complex_tab(to_join, i);
	return (to_ret);
}

void	replace_piece(t_token *list, t_data *data)
{
	char	*temp;

	temp = NULL;
	while (list)
	{
		if (list->type != S_QUOTE && check_expand(list->piece))
		{
			temp = gen_expand_line(list->piece, data->my_env, list);
			free(list->piece);
			list->piece = temp;
		}
		list = list->next;
	}
}

void	attribute_rdir_type(t_token *node)
{
	char	*cursor;

	cursor = node->piece;
	while (is_space(*cursor))
		cursor++;
	if (*cursor == '<')
	{
		if (*(cursor + 1) && *(cursor + 1) == '<')
			node->type = HEREDOC;
		else
			node->type = INFILE;
	}
	if (*cursor == '>')
	{
		if (*(cursor + 1) && *(cursor + 1) == '>')
			node->type = APPEND;
		else
			node->type = OUTFILE;
	}
	cursor = sanitize(node->piece);
	free(node->piece);
	node->piece = cursor;
}

void	replace_piece_redir(t_token *list, t_data *data)
{
	char	*temp;

	temp = NULL;
	while (list)
	{
		if (list->type == REDIR)
			attribute_rdir_type(list);
		if (list->type != HEREDOC && list->type != S_QUOTE
			&& check_expand(list->piece))
		{
			temp = gen_expand_line(list->piece, data->my_env, list);
			free(list->piece);
			list->piece = temp;
		}
		if (list->type == HEREDOC && list->block_end)
			list = list->block_end;
		list = list->next;
	}
}

void	expand_in_list(t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		replace_piece(cmd->current_cmd, data);
		replace_piece_redir(cmd->rdir_list, data);
		cmd = cmd->next;
	}
}
