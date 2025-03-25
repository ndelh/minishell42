/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:25:24 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 12:21:41 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*split_replace(char *s)
{
	char	*to_ret;
	char	**split;
	int		i;

	split = split_w_space(s);
	if (!split || !*split)
		return (NULL);
	i = 1;
	to_ret = *split;
	while (split[i])
	{
		to_ret = join_with_space(to_ret, split[i]);
		i++;
	}
	free(split);
	return (to_ret);
}

char	*ft_replace(t_data *data, char *s, t_env *env, t_token *list)
{
	char	*to_ret;

	to_ret = NULL;
	s++;
	if (*s == '?')
		to_ret = ft_itoa(data->exit % 255);
	while (env)
	{
		if (!ft_strcmp(s, env->name))
		{
			if (list && list->type == D_QUOTE)
				to_ret = ft_strdup(env->content);
			else
				to_ret = split_replace(env->content);
		}
		env = env->next;
	}
	return (to_ret);
}

void	replace_expand(t_data *data, char **tab, t_env *env, t_token *list)
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
			modified = ft_replace(data, *tab, env, list);
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
