/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:08:15 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/09 17:08:55 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_end(t_data *data)
{
	free_env_list(data->my_env);
	if (data->cmd_list)
		free_cmd_list(data->cmd_list);
	ft_free_tab(data->envpath);
	free(data);
}
