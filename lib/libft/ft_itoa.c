/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:56:32 by ndelhota          #+#    #+#             */
/*   Updated: 2024/10/13 13:50:28 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itolen(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	if (n == 0)
	{
		len++;
		return (len);
	}
	while (n >= 1)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_int_min(void)
{
	char		*i;

	i = ft_calloc(1, 12);
	i[0] = '-';
	i[1] = '2';
	i[2] = '1';
	i[3] = '4';
	i[4] = '7';
	i[5] = '4';
	i[6] = '8';
	i[7] = '3';
	i[8] = '6';
	i[9] = '4';
	i[10] = '8';
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*itoa;

	if (n == -2147483648)
	{
		itoa = ft_int_min();
		return (itoa);
	}
	i = ft_itolen(n);
	itoa = ft_calloc(1, i + 1);
	if (!itoa)
		return (0);
	if (n == 0)
		itoa[0] = '0';
	if (n < 0)
	{
		itoa[0] = '-';
		n = n * -1;
	}
	while (n >= 1 && itoa[i] != '-')
	{
		itoa[i-- - 1] = n % 10 + '0';
		n /= 10;
	}
	return (itoa);
}
