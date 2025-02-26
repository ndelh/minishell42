/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:13 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/10 11:31:33 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long int	i;
	unsigned char		*p;

	p = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)&s[i]);
		else
			i++;
	}
	return (((void *)0));
}
