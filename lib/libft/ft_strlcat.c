/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:25:41 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/17 14:04:18 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	if (n == 0 || n <= ft_strlen(dst))
		return (n + ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	while (src[j] && i + 1 < n)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src + j));
}
