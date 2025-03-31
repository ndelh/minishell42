/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_envp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:24:19 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/19 20:26:49 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	envp_size(t_env *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->status)
			count++;
		list = list->next;
	}
	return (count);
}

void	fill_ret(char **tab, t_env *list)
{
	int	len;

	while (list)
	{
		if (list->status)
		{
			len = ft_strlen(list->name) + ft_strlen(list->content) + 2;
			*tab = ft_calloc(sizeof(char), len);
			ft_strlcat(*tab, list->name, len);
			ft_strlcat(*tab, "=", len);
			ft_strlcat(*tab, list->content, len);
			tab++;
		}
		list = list->next;
	}
	*tab = NULL;
}

char	**convert_envp(t_env *my_env)
{
	char	**to_ret;
	int		size;

	size = envp_size(my_env);
	to_ret = malloc(sizeof(char *) * (size + 1));
	fill_ret(to_ret, my_env);
	return (to_ret);
}
