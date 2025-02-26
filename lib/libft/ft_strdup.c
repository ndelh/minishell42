/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 06:28:32 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/11 06:58:40 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	i = ft_strlen(s);
	dup = ft_calloc(1, i + 1);
	if (!dup)
		return (0);
	ft_memcpy(dup, s, i);
	return (dup);
}
