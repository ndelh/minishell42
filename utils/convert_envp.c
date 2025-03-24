/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:51:55 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 10:13:27 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	envp_size(t_env *list)
{
	int	count;

	count = 0;
	while (list)
	{
		list++;
		count++;
	}
	return (count);
}

void	fill_ret(char **tab, t_env *env, int size)
{
	int	len;

	while (list)
	{
		len = ft_strlen(list->name) + ft_strlen(list->content) + 2;
		*tab = ft_calloc(sizeof(char), len);
		ft_stlrcat(*tab, list->name, len);
		ft_stlrcat(*tab, "", len);
		ft_stlrcat(*tab, list->content, len);
		list = list->next;
		env++;
	}
}

char	**convert_envp(t_env *my_env)
{
	char	**to_ret;
	int		size;

	size = envp(my_env);
	to_ret = malloc(sizeof(t_env *) * (size + 1));
	if (!to_ret)
		return (NULL);
	fill_ret(to_ret);
}
