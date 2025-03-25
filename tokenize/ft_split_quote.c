/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:42:28 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 12:17:58 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_single(char **s)
{
	(*s)++;
	while (**s && **s != '\'')
	{
		(*s)++;
	}
	(*s)++;
}

void	skip_double(char **s)
{
	(*s)++;
	while (**s && **s != '\"')
		(*s)++;
	(*s)++;
}

int	word_numb(char *s)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (*s == '\'')
		{
			ret++;
			skip_single(&s);
		}
		if (*s == 34)
		{
			ret++;
			skip_double(&s);
		}
		if (*s && *s != '\'' && *s != '\"')
		{
			ret++;
			s++;
			while (*s && *s != '\'' && *s != 34)
				s++;
		}
	}
	return (ret);
}

char	*ft_dup(char **s)
{
	char	*cursor;
	char	*ret;

	cursor = *s;
	if (*cursor == '\"')
		skip_double(&cursor);
	else if (*cursor == '\'')
		skip_single(&cursor);
	else
	{
		while (*cursor && *cursor != '\'' && *cursor != '\"')
			cursor++;
	}
	ret = ft_substr(*s, 0, ft_strlen(*s) - ft_strlen(cursor));
	*s = cursor;
	return (ret);
}

char	**split_quote(char *s)
{
	char	**to_ret;
	int		i;
	int		nb;

	i = 0;
	nb = word_numb(s);
	to_ret = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!to_ret)
		return (NULL);
	while (i < nb)
	{
		to_ret[i] = ft_dup(&s);
		i++;
	}
	to_ret[i] = NULL;
	return (to_ret);
}
