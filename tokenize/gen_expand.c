/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:25:24 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 15:15:35 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_replace(char *s, t_env *env)
{
	char	*to_ret;

	to_ret = NULL;
	s++;
	while (env)
	{
		if (!ft_strncmp(s, env->name, ft_strlen(s) + 1))
		{
			to_ret = ft_strdup(env->content);
		}
		env = env->next;
	}
	return (to_ret);
}

void	replace_expand(char **tab, t_env *env)
{
	char	*modified;

	modified = NULL;
	while (*tab)
	{
		if (ft_strlen(*tab) == 1 && **tab == '$')
		{
			free(*tab);
			*tab = NULL;
		}
		else if (check_expand(*tab))
		{
			modified = ft_replace(*tab, env);
			free(*tab);
			*tab = modified;
		}
		tab++;
	}
}

int	component_len(char **tab, int i)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (j < i)
	{
		len += ft_strlen(*tab);
		tab++;
		j++;
	}
	return (len);
}

char	*ft_mend_line(char **tab, int i)
{
	char	*mending;
	int		j;

	j = (component_len(tab, i) + 1);
	mending = malloc(sizeof(char) * (j));
	ft_memset(mending, 0, j);
	j = 0;
	while (j < i)
	{
		if (*tab)
			ft_strlcat(mending, *tab, ft_strlen(mending) + ft_strlen(*tab) + 1);
		j++;
		tab++;
	}
	return (mending);
}
