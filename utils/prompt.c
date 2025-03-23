/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:42:30 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/23 18:13:54 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*refine_after_user(char *cursor, t_env *node, char *prompt)
{
	char	*to_ret;
	char	*modify;

	modify = ft_substr(cursor, 0, ft_strlen(cursor));
	free(prompt);
	to_ret = ft_vastrjoin(3, node->content, ":~", modify);
	free(modify);
	return (to_ret);
}

char	*refine_before_user(t_env *node, char *prompt)
{
	char	*to_ret;
	char	*modify;
	char	*cursor;

	cursor = ft_strnstr(prompt, node->content, ft_strlen(prompt));
	modify = ft_substr(prompt, 0, ft_strlen(prompt) - ft_strlen(cursor));
	free(prompt);
	to_ret = ft_vastrjoin(3, node->content, ":~", modify);
	free(modify);
	return (to_ret);
}

void	move_cursor_prompt(char **username, char **cursor)
{
	while ((**username && **cursor) && (**cursor == **username))
	{
		(*cursor)++;
		(*username)++;
	}
}

void	refine_prompt(char **prompt, t_data *data)
{
	t_env	*node;
	char	*username;
	char	*cursor;

	node = go_to_env_node(data->my_env, "USER");
	if (node)
	{
		username = node->content;
		cursor = ft_strnstr(*prompt, username, ft_strlen(*prompt));
		move_cursor_prompt(&username, &cursor);
		if (*cursor)
			*prompt = refine_after_user(cursor, node, *prompt);
		else
			*prompt = refine_before_user(node, *prompt);
	}
}

void	ft_prompt(char **display, t_data *data)
{
	char	*to_merge;

	if (*display)
	{
		free(*display);
		*display = NULL;
	}
	else
	{
		to_merge = get_pwd(data);
		if (data->my_env)
			refine_prompt(&to_merge, data);
		*display = ft_strjoin(to_merge, "$ ");
		free(to_merge);
	}
}
