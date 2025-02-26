/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:14:08 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/12 17:33:27 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = ft_calloc(1, i + j + 1);
	if (!join)
		return (0);
	ft_strlcat(join, s1, i + 1);
	ft_strlcat(join, s2, i + j + 1);
	return (join);
}
