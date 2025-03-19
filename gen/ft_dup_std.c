/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_std.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:30:07 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/19 16:49:52 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_std(t_data *data)
{
	data->standard_out = -1;
	data->standard_in = dup(0);
	if (data->standard_in == -1)
	{
		perror("stock [0]");
		ft_end(data);
	}
	data->standard_out = dup(1);
	if (data->standard_out == -1)
	{
		perror("stock [1]");
		ft_end(data);
	}
}
