/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exec01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:21:42 by agamay            #+#    #+#             */
/*   Updated: 2025/03/31 16:22:11 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks list of redirs in cmd block. Opens them.
static void	open_files(t_data *data, t_cmd *cmd, int prev)
{
	t_token	*rdir_list;

	rdir_list = cmd->rdir_list;
	while (rdir_list)
	{
		if (rdir_list->type == 4 || rdir_list->type == 6)
			rdir_list->fd = open (rdir_list->piece, O_RDONLY);
		else if (rdir_list->type == 5)
			rdir_list->fd = open (rdir_list->piece,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (rdir_list->type == 7)
			rdir_list->fd = open (rdir_list->piece,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (rdir_list->fd == -1)
		{
			closer(1, prev);
			redir_error(data, cmd, rdir_list);
		}
		rdir_list = rdir_list->next;
	}
}

//checks if the first arg of cmd->cmd_arg exists, and it's nature.
static void	check_access(t_data *data, t_cmd *cmd, int prev)
{
	char	*cmd_path;
	int		i;

	if (!cmd->cmd_arg || cmd->buildin)
		return ;
	i = -1;
	while (data->envpath && data->envpath[++i])
	{
		cmd_path = ft_vastrjoin(3, data->envpath[i], "/", cmd->cmd_arg[0]);
		if (!check_nature(data, cmd, cmd_path))
		{
			cmd->cmd_path = cmd_path;
			return ;
		}
		free(cmd_path);
	}
	if (!check_nature(data, cmd, cmd->cmd_arg[0]))
	{
		abs_path(cmd);
		return ;
	}
	closer(1, prev);
	fct_error(data, cmd);
}

//redirects stdin and stdout in pipes or in redis,
//then execs cmd or calls builtin.
static void	exec_cmd(t_data *data, t_cmd *cmd, int prev)
{
	t_token	*rdir_list;

	rdir_list = cmd->rdir_list;
	if (cmd->previous)
		secured_dup2(data, prev, 0);
	if (cmd->next)
		secured_dup2(data, cmd->pfd[1], 1);
	closer(3, prev, cmd->pfd[0], cmd->pfd[1]);
	if (!cmd->buildin)
		closer(2, data->standard_in, data->standard_out);
	while (rdir_list)
	{
		if (rdir_list->type == 4 || rdir_list->type == 6)
			secured_dup2(data, rdir_list->fd, 0);
		if (rdir_list->type == 6)
			unlink(rdir_list->piece);
		else if (rdir_list->type == 5 || rdir_list->type == 7)
			secured_dup2(data, rdir_list->fd, 1);
		close(rdir_list->fd);
		rdir_list = rdir_list->next;
	}
	call_or_exec(data, cmd);
}

//forks and executes each cmd.
//Then waits for each child in creation order.
static void	handle_pipes(t_data *data, t_cmd *cmd)
{
	int		prev;

	prev = -1;
	while (cmd)
	{
		secured_pipe(data, cmd);
		cmd->pid = secured_fork(data);
		if (cmd->pid == 1)
		{
			open_files(data, cmd, prev);
			check_access(data, cmd, prev);
			exec_cmd(data, cmd, prev);
		}
		closer(1, prev);
		prev = dup(cmd->pfd[0]);
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		cmd = cmd->next;
	}
	closer(1, prev);
	waiter(data, data->cmd_list);
}

//recieves all cmds. Forks if we have pipes or no build-ins.
void	start_exec(t_data *data)
{
	t_cmd	*cmd;

	data->envpath = set_path(data);
	cmd = data->cmd_list;
	if (!cmd->next && cmd->buildin)
	{
		open_files(data, cmd, -1);
		exec_cmd(data, cmd, 0);
	}
	else
		handle_pipes(data, cmd);
	assign_(data);
}
