/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_mns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:45:42 by agamay            #+#    #+#             */
/*   Updated: 2025/04/14 12:45:48 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	increment_shlvl(t_data *data)
{
	t_env	*shlvl;
	int		lvl;

	shlvl = go_to_env_node(data->my_env, "SHLVL");
	if (shlvl)
	{
		lvl = ft_atoi(shlvl->content);
		lvl++;
		free (shlvl->content);
		shlvl->content = ft_itoa(lvl);
	}
	data->envp = convert_envp(data->my_env);
}

//deals with sig for mns recursion
int	mns_mns(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (cmd->pid != 1)
		cmd->pid = secured_fork(data);
	if (cmd->pid == 1)
	{
		closer(2, data->standard_in, data->standard_out);
		increment_shlvl(data);
		execve("./minishell", cmd->cmd_arg, data->envp);
		perror("execve failed");
		ft_end(data);
		exit(127);
	}
	signals_init(3);
	ret = waiter(data, cmd);
	return (ret);
}
