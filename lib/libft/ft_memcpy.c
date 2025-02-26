/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:28:50 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/13 17:04:51 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*desta;
	unsigned char	*srca;
	size_t			i;

	srca = (unsigned char *)src;
	desta = (unsigned char *)dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		desta[i] = srca[i];
		i++;
	}
	return (dest);
}
