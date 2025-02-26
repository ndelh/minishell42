/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:11:28 by ndelhota          #+#    #+#             */
/*   Updated: 2024/11/13 07:38:06 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (!*str1 && !*str2)
		return (0);
	i = 0;
	while ((*str1 || *str2) && (i < n))
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		str1++;
		str2++;
		i++;
	}
	return (0);
}
