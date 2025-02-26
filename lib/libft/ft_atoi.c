/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <ndelhota@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:23 by ndelhota          #+#    #+#             */
/*   Updated: 2024/11/27 14:37:39 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

long long int	ft_atoi(const char *nptr)
{
	long long int	nb;
	long long int	neg;

	nb = 0;
	neg = 1;
	while ((*nptr == 32) || (*nptr <= 13 && *nptr >= 9))
		nptr++;
	if ((*nptr == '+') || (*nptr == '-'))
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while ((*nptr) && (*nptr >= '0' && (*nptr <= '9')))
	{
		nb = (nb * 10 + (*nptr - 48));
		if (nb * neg > 2147483647 || nb * neg < -2147483648)
			return (nb * neg);
		nptr++;
	}
	return (nb * neg);
}
