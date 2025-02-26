/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:20:37 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/13 16:56:12 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int search)
{
	size_t	i;

	i = 0;
	if ((unsigned char)search == 0)
	{
		i = ft_strlen(str);
		return ((char *)str + i);
	}
	while (str[i])
	{
		if (str[i] == (unsigned char)search)
		{
			return ((char *)str + i);
		}
		else
			i++;
	}
	return ((char *)0);
}
