/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:48:40 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/14 14:15:25 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*cursor;

	while (env)
	{
		cursor = env->next;
		free(env->name);
		free(env->content);
		free(env);
		env = cursor;
	}
}

void	free_token_list(t_token *to_free)
{
	t_token	*temp;

	while (to_free)
	{
		temp = to_free->next;
		if (to_free->type == HEREDOC)
			unlink(to_free->piece);
		if (to_free->fd > 2)
			close(to_free->fd);
		free(to_free->piece);
		free(to_free);
		to_free = temp;
	}
}

void	free_cmd_list(t_cmd *list)
{
	t_cmd	*temp;
	int	nb;

	nb = 1;	
	temp = list;
	while (list)
	{
		temp = list->next;
		ft_free_tab(list->cmd_arg);
		free_line_list(&list->cmd_line);
		free_token_list(list->rdir_list);
		free_line_list(&list->redir_line);
		free(list);
		nb++;
		list = temp;
	}
}
