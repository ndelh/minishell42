/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:08:15 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/24 11:46:35 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_alloc(void *alloc, t_data *data)
{
	if (!alloc)
	{
		perror("allocation failed:");
		ft_end(data);
		exit (1);
	}
}

void	close_fds(t_data *data)
{
	if (data->standard_out != -1)
		close(data->standard_out);
	if (data->standard_in != -1)
		close(data->standard_in);
}

void	ft_end(t_data *data)
{
	free_env_list(data->my_env);
	closer(2, data->standard_in, data->standard_out);
	if (data->cmd_list)
		free_cmd_list(data->cmd_list);
	ft_free_tab(data->envpath);
	ft_free_tab(data->envp);
	free(data);
}
