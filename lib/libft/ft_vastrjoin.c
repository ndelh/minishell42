/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vastrjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:04:10 by agamay            #+#    #+#             */
/*   Updated: 2024/11/26 15:05:05 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static size_t	ft_vastrlen(int n, va_list str)
{
	size_t	len;

	len = 0;
	while (n--)
		len = len + ft_strlen(va_arg(str, char *));
	return (len);
}

char	*ft_vastrjoin(size_t n, ...)
{
	char	*dest;
	char	*temp;
	char	*vastr;
	size_t	size;
	va_list	str;

	va_start(str, n);
	size = ft_vastrlen(n, str);
	va_end(str);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	temp = dest;
	va_start(str, n);
	while (n--)
	{
		vastr = va_arg(str, char *);
		while (*vastr)
			*temp++ = *vastr++;
	}
	va_end(str);
	*temp = '\0';
	return (dest);
}
