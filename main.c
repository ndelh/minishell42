/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:29:19 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 16:46:23 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int ac, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	data = NULL;
	argv = NULL;
	g_status = 0;//$? will expand to this var.
	if (ac == 1)
	{
		ft_gen(&data, envp);
		while (1)
		{
			line = readline("minishell > ");
			if (line == NULL)
				mns_exit(data, NULL);
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
		ft_end(data);
	}
	return (g_status % 255);
}
