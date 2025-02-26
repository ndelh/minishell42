/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:56 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/13 17:10:13 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size_dest)
{
	size_t	i;
	size_t	src_size;

	src_size = ft_strlen(src);
	i = 0;
	if (size_dest != 0)
	{
		while (src[i] && i < (size_dest - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_size);
}
