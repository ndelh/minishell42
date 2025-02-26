/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:35:31 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/13 17:11:13 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_trim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (s1[i] != set[j] && set[j])
			j++;
		if (!set[j])
			return (i);
		i++;
		j = 0;
	}
	if (!*s1)
		i = 0;
	return (i);
}

static int	ft_reverse_trim(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (i > 0)
	{
		while (s1[i] != set[j] && set[j])
		{
			j++;
			if (!set[j])
				return (i);
		}
		i--;
		j = 0;
	}
	return (ft_strlen(s1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	j;

	i = ft_trim(s1, set);
	j = ft_reverse_trim(s1, set);
	if (i == 0 && j == 0)
	{
		trim = ft_calloc(1, 1);
		if (!trim)
			return (0);
	}
	else
	{
		trim = ft_substr(s1, i, j - i + 1);
		if (!trim)
			return (0);
	}
	return (trim);
}
