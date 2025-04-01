/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:36:08 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 12:59:06 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_char(char *s, char a)
{
	int	count;

	if (ft_strlen(s) == 1)
		return (1);
	count = 1;
	if (*s && *s == a)
		s++;
	while (*s)
	{
		if (*s == a)
			count++;
		s++;
	}
	return (count);
}

char	*ft_dup_charac(char **s, char a)
{
	char	*to_ret;
	char	*cursor;
	int		i;

	cursor = *s;
	if (*cursor == a)
		cursor++;
	while (*cursor && *cursor != a)
		cursor++;
	i = ft_strlen(*s) - ft_strlen(cursor);
	to_ret = ft_substr(*s, 0, i);
	*s = cursor;
	return (to_ret);
}

char	**split_at_char(char *s, char c)
{
	int		n;
	char	**to_ret;
	int		i;

	i = 0;
	n = count_char(s, c);
	to_ret = malloc(sizeof(char *) * (n + 1));
	if (!to_ret)
		return (NULL);
	while (i < n)
	{
		to_ret[i] = ft_dup_charac(&s, c);
		i++;
	}
	to_ret[i] = NULL;
	return (to_ret);
}
