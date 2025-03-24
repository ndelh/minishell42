/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:48:40 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/24 11:52:33 by ndelhota         ###   ########.fr       */
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

void	free_token_list(t_token *to_free, int i)
{
	t_token	*temp;

	while (to_free)
	{
		temp = to_free->next;
		if (i)
		{
			printf("%s\n", to_free->piece);
			printf("%d\n", to_free->type);
			if (to_free->type == HEREDOC)
				unlink(to_free->piece);
		}
		free(to_free->piece);
		free(to_free);
		to_free = temp;
	}
}

void	free_cmd_list(t_cmd *to_free)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	while (to_free)
	{
		temp = to_free->next;
		printf("struct numero :%d\n", i);
		printf("exec_line\n");
		if (to_free->cmd_arg)
		{
			print_complex_tab(to_free->cmd_arg, to_free->tab_line);
			free_complex_tab(to_free->cmd_arg, to_free->tab_line);
		}
		free_token_list(to_free->current_cmd, 0);
		printf("redir_line\n");
		free_token_list(to_free->rdir_list, 1);
		free(to_free);
		to_free = temp;
		i++;
	}
}
