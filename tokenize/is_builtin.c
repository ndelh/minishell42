/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:36:16 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 18:51:40 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_build(char **s)
{
	if (!s || !*s)
		return (0);
	if (!ft_strcmp(*s, "echo") || !ft_strcmp(*s, "env")
		|| !ft_strcmp(*s, "unset") || !ft_strcmp(*s, "export")
		|| !ft_strcmp(*s, "pwd") || !ft_strcmp(*s, "cd")
		|| !ft_strcmp(*s, "minishell")
		|| !ft_strcmp(*s, "exit"))
		return (1);
	printf("no build\n");
	return (0);
}

void	is_builtin(t_cmd *list)
{
	while (list)
	{
		if (is_build(list->cmd_arg))
			list->buildin = 1;
		list = list->next;
	}
}
