/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:47:24 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/17 09:15:21 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (start >= i)
	{
		sub = ft_calloc(1, 1);
		if (!sub)
			return (0);
		return (sub);
	}
	i = i - start;
	if (i > len)
		i = len;
	sub = ft_calloc(1, i + 1);
	if (!sub)
		return (0);
	ft_memcpy(sub, s + start, i);
	return (sub);
}
