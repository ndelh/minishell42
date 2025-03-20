/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:29:19 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 09:47:43 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	data = NULL;
	argv = NULL;
	if (ac == 1)
	{
		ft_gen(&data, envp);
		while (1)
		{
			line = readline("minishell > ");
			if (line == NULL)
				break ;
			add_history(line);
			ft_tokenize(data, line);
			free_cmd_list(data->cmd_list);
			data->cmd_list = NULL;
			free(line);
		}
		ft_free_tab(data->envp);
		ft_end(data);
	}
}
