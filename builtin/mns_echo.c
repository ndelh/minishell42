/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:45:35 by agamay            #+#    #+#             */
/*   Updated: 2025/03/31 16:45:40 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_flagvalid(char *arg)
{
	while (*(++arg) == 'n')
	{
	}
	if (!*arg)
		return (1);
	return (0);
}

//print given args with a \n. -n removes the \n.
int	mns_echo(t_cmd *cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd->cmd_arg[i] && cmd->cmd_arg[i][0] == '-'
		&& is_flagvalid(cmd->cmd_arg[i]))
	{
		i++;
		n = 1;
	}
	while (cmd->cmd_arg[i])
	{
		ft_putstr_fd(cmd->cmd_arg[i], 1);
		if (cmd->cmd_arg[++i])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}
