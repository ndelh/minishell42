/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:22:55 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/17 11:59:19 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_len;
	size_t	needle_len;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	haystack_len = 0;
	while (haystack[haystack_len] != '\0')
	{
		needle_len = 0;
		while (haystack[haystack_len + needle_len] == needle[needle_len]
			&& (haystack_len + needle_len) < len)
		{
			if (haystack[haystack_len + needle_len] == '\0'
				&& needle[needle_len] == '\0')
				return ((char *)&haystack[haystack_len]);
			needle_len++;
		}
		if (needle[needle_len] == '\0')
			return ((char *)haystack + haystack_len);
		haystack_len++;
	}
	return (0);
}
