/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:55:46 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/23 19:01:38 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	read_loop(t_data *data)
{
	char	*line;
	char	*display;

	display = NULL;
	while (1)
	{
		g_signal = 0;
		ft_prompt(&display, data);
		line = readline(display);
		ft_prompt(&display, data);
		if (line == NULL)
			mns_exit(data, NULL);
		if (g_signal == SIGINT)
			data->exit = 130;//$? will expand to this var.
		if (primal_parse(line))
		{
			add_history(line);
			ft_tokenize(data, line);
			start_exec(data);
			free_cmd_list(data->cmd_list);
			data->cmd_list = NULL;
		}
		free(line);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_data	*data;

	argv = NULL;
	data = NULL;
	if (ac != 1)
		return (g_status % 255);
	ft_gen(&data, envp);
	read_loop(data);
	ft_free_tab(data->envp);
	ft_end(data);
	return (g_status % 255);
}
