/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:14:53 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/17 09:21:58 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	size_t	i;
	char	*m;

	if (!s || !f)
		return (0);
	i = 0;
	m = ft_calloc(1, ft_strlen(s) + 1);
	if (!m)
		return (0);
	while (i < ft_strlen(s))
	{
		m[i] = f(i, s[i]);
		i++;
	}
	return (m);
}
