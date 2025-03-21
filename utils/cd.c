/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:34:28 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 15:55:29 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_cd(char *s, t_env *list)

void	exec_cd(char **args, t_data *data)
{
	if (tab_len(args == 2))
		go_cd(args[1], data->my_env);
	if (tab_len(args) > 2)
		ft_putendl("cd :to_many->args", 2);
	if (tab_len(args) == 1)
		ft_putendl("cd :to_few_args", 2);
}
