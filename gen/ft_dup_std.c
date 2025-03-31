/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_std.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:30:07 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/27 18:54:31 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_std(t_data *data)
{
	data->standard_out = -1;
	data->standard_in = dup(STDIN_FILENO);
	if (data->standard_in == -1)
	{
		perror("stock [0]");
		mns_exit(data, NULL);
	}
	data->standard_out = dup(STDOUT_FILENO);
	if (data->standard_out == -1)
	{
		perror("stock [1]");
		mns_exit(data, NULL);
	}
}
