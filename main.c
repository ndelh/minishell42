/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:55:46 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/02 16:10:40 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	tokenize_exec(t_data *data, char *line)
{
	if (primal_parse(line) && check_first_char(line))
	{
		add_history(line);
		ft_tokenize(data, line);
		if (data->cmd_list)
			start_exec(data);
		free_cmd_list(data->cmd_list);
		data->cmd_list = NULL;
	}
	else if (line && *line)
		data->exit = 2;
}

void	read_loop(t_data *data)
{
	char	*line;
	char	*display;

	display = NULL;
	while (1)
	{
		ft_prompt(&display, data);
		line = readline(display);
		ft_prompt(&display, data);
		if (g_signal == SIGINT)
		{
			data->exit = 130;
			secured_dup2(data, data->standard_in, STDIN_FILENO);
		}
		if (line == NULL && g_signal != 2)
		{
			rl_clear_history();
			mns_exit(data, NULL);
		}
		tokenize_exec(data, line);
		g_signal = 0;
		free(line);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_data	*data;

	argv = NULL;
	data = NULL;
	rl_catch_signals = 0;
	if (ac != 1)
		return (0);
	ft_gen(&data, envp);
	read_loop(data);
}
