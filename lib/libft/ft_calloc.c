/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:17:54 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/11 07:18:19 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	a_size;

	if (nmemb >= 65535 || size >= 65535)
		return (NULL);
	a_size = (nmemb * size);
	if (a_size <= 0)
		array = malloc(1);
	else
		array = malloc(a_size);
	if (!array)
		return (0);
	ft_bzero(array, a_size);
	return (array);
}
