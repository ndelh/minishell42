/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:30:58 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 13:03:09 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_redir(char **s)
{
	(*s)++;
	if (**s == *(*s - 1))
		(*s)++;
	while (**s && is_space(**s))
		(*s)++;
	while (**s && (!is_space(**s) && **s != '<' && **s != '>' ))
		(*s)++;
	if (**s && is_space(**s))
		(*s)++;
}

int	count_redir(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s && (*s == '<' || *s == '>'))
		{
			count++;
			skip_redir(&s);
		}
		while (is_space(*s))
			s++;
		if (*s && *s != '<' && *s != '>')
			count++;
		while (*s && *s != '<' && *s != '>')
			s++;
	}
	return (count);
}

char	*dup_redir(char **s)
{
	char	*cursor;
	char	*to_ret;
	int		i;

	cursor = *s;
	while (*cursor == ' ')
		cursor++;
	if (*cursor == '<' || *cursor == '>')
		skip_redir(&cursor);
	else
	{
		while (*cursor && *cursor != '<' & *cursor != '>')
			cursor++;
	}
	i = ft_strlen(*s) - ft_strlen(cursor);
	to_ret = ft_substr(*s, 0, i);
	*s = cursor;
	return (to_ret);
}

char	**split_at_redir(char *s)
{
	char	**to_ret;
	char	**cursor;
	int		nb;
	int		i;

	i = 0;
	nb = count_redir(s);
	to_ret = malloc(sizeof(char *) * (nb + 1));
	if (!to_ret)
		return (NULL);
	cursor = to_ret;
	while (i < nb)
	{
		cursor[i] = dup_redir(&s);
		i++;
	}
	cursor[i] = NULL;
	return (to_ret);
}
