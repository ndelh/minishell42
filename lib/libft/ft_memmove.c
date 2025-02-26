/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:53:47 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/11 06:05:00 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*cdest;
	char	*csrc;

	if (!dest && !src)
		return (0);
	cdest = (char *)dest;
	csrc = (char *)src;
	if (cdest <= csrc)
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	if (cdest > csrc)
	{
		cdest += n - 1;
		csrc += n - 1;
		while (n--)
			*cdest-- = *csrc--;
	}
	return (dest);
}
