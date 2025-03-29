/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:44:26 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/24 12:02:12 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_last_env(t_env **list, t_env *to_add)
{
	static t_env	*cursor;

	if (!*list || !list)
		*list = to_add;
	else
	{
		cursor->next = to_add;
		to_add->previous = cursor;
	}
	cursor = to_add;
}

void	ft_add_string(t_env *node, char *s)
{
	char	*cursor;

	cursor = ft_strchr(s, '=');
	if (!cursor)
		node->name = ft_strdup(s);
	else
	{
		node->name = ft_substr(s, 0, (ft_strlen(s) - ft_strlen(cursor)));
		node->content = ft_substr(cursor, 1, ft_strlen(cursor) - 1);
		node->status = 1;
	}
}

t_env	*ft_gen_env_node(char *s)
{
	t_env	*to_ret;

	to_ret = malloc(sizeof(t_env));
	ft_memset(to_ret, 0, sizeof(t_env));
	ft_add_string(to_ret, s);
	return (to_ret);
}

t_env	*ft_gen_env_list(char **envp)
{
	t_env	*to_ret;
	t_env	*to_add;

	to_ret = NULL;
	while (*envp)
	{
		to_add = ft_gen_env_node(*envp);
		ft_add_last_env(&to_ret, to_add);
		envp++;
	}
	return (to_ret);
}

void	ft_gen(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	check_alloc(*data, *data);
	signals_init(0);
	ft_memset(*data, 0, sizeof(t_data));
	ft_dup_std(*data);
	(*data)->my_env = ft_gen_env_list(envp);
	(*data)->envp = convert_envp((*data)->my_env);
}
