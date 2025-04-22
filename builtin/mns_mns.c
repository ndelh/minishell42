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

static int	mns_check_nature(t_cmd *cmd)
{
	struct stat	st_buff;

	st_buff.st_mode = -1;
	stat(cmd->cmd_arg[0], &st_buff);
	if (**(cmd->cmd_arg) && S_ISDIR(st_buff.st_mode))
	{
		errno = EISDIR;
		perror(cmd->cmd_arg[0]);
		return (126);
	}
	if (**(cmd->cmd_arg) && access(cmd->cmd_arg[0], X_OK))
	{
		if (ft_strchr(cmd->cmd_arg[0], '/'))
			perror(cmd->cmd_arg[0]);
		else
		{
			ft_putstr_fd(cmd->cmd_arg[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		return (127);
	}
	return (0);
}

//deals with sig for mns recursion
int	mns_mns(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = mns_check_nature(cmd);
	if (ret)
		return (ret);
	if (cmd->pid != 1)
		cmd->pid = secured_fork(data);
	if (cmd->pid == 1)
	{
		closer(2, data->standard_in, data->standard_out);
		increment_shlvl(data);
		execve(cmd->cmd_arg[0], cmd->cmd_arg, data->envp);
		perror("execve failed");
		ft_end(data);
		exit(127);
	}
	signals_init(3);
	ret = waiter(data, cmd);
	return (ret);
}
