/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:36:11 by ndelhota          #+#    #+#             */
/*   Updated: 2024/11/19 15:18:44 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	wordlen;
	int		i;
	char	**split;

	i = 0;
	split = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!s || !split)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		if (!ft_strchr(s, c))
			wordlen = ft_strlen(s);
		else
			wordlen = ft_strchr(s, c) - s;
		split[i++] = ft_substr(s, 0, wordlen);
		s += wordlen;
	}
	split[i] = NULL;
	return (split);
}
