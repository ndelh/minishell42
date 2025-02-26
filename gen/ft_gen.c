/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:44:26 by ndelhota          #+#    #+#             */
/*   Updated: 2025/02/26 12:12:00 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_envp(char **envp)
{
	char	**to_ret;
	int		i;

	to_ret = (char **)malloc(sizeof(char *) * (tab_len(envp) + 1));
	if (!to_ret)
		exit (0);
	i = 0;
	while (i < tab_len(envp))
	{
		to_ret[i] = ft_strdup(envp[i]);
		i++;
	}
	to_ret[i] = NULL;
	return (to_ret);
}

void	ft_gen(t_data **data, char **envp)
{
	t_data	*to_ret;

	to_ret = malloc(sizeof(t_data));
	if (to_ret)
	{
		to_ret->my_env = ft_get_envp(envp);
	}
	*data = to_ret;
}
