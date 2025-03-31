/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:13:17 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 12:14:18 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expand(char *s)
{
	while (*s && *s != '$')
		s++;
	if (*s)
		return (1);
	else
		return (0);
}

void	skip_expand(char **s)
{
	(*s)++;
	if (**s && (**s == '?' || ft_isdigit(**s)))
	{
		(*s)++;
		return ;
	}
	if (**s && **s == '_')
		(*s)++;
	if (!**s || !ft_isalpha(**s))
		return ;
	while (**s && ft_isalnum(**s))
		(*s)++;
}

int	count_expand_split(char *s)
{
	int	nb;

	nb = 0;
	while (*s)
	{
		while (*s == '$')
		{
			nb++;
			skip_expand(&s);
		}
		if (*s)
		{
			nb++;
			while (*s && *s != '$')
				s++;
		}
	}
	return (nb);
}

void	move_cursor(char **cursor)
{
	char	*to_move;

	if (**cursor && **cursor == '$')
	{
		to_move = *cursor;
		skip_expand(&to_move);
		*cursor = to_move;
	}
	else
	{
		while (**cursor && **cursor != '$')
			(*cursor)++;
	}
}

char	**isolate_expand(char *s, int i)
{
	char	**to_ret;
	int		j;
	char	*cursor;

	to_ret = malloc(sizeof(char *) * (i + 1));
	if (!to_ret)
		return (NULL);
	j = 0;
	cursor = s;
	while (j < i)
	{
		move_cursor(&cursor);
		to_ret[j] = ft_substr(s, 0, ft_strlen(s) - ft_strlen(cursor));
		s = cursor;
		j++;
	}
	to_ret[j] = NULL;
	return (to_ret);
}
