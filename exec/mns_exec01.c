#include "../minishell.h"

static void	call_or_exec(t_data *data, t_cmd *cmd)
{
	if (cmd->buildin)
		call_builtin(data, cmd);
	else
	{
		execve(cmd->cmd_path, cmd->cmd_arg, data->envp);
		perror("execve failed");
		ft_end(data);
		exit(127);
	}
}

//checks list of redirs in cmd block. Opens them.
static void	open_files(t_data *data, t_cmd *cmd)
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
			redir_error(data, cmd, rdir_list);
		rdir_list = rdir_list->next;
	}
}

//redirects stdin and stdout in pipes or in redis, then execs cmd.
static void	exec_cmd(t_data *data, t_cmd *cmd, int prev)
{
	t_token	*rdir_list;

	rdir_list = cmd->rdir_list;
	if (cmd->previous)
		secured_dup2(data, prev, 0);
	if (cmd->next)
		secured_dup2(data, cmd->pfd[1], 1);
	closer(3, prev, cmd->pfd[0], cmd->pfd[1]);
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
static void	handle_pipes(t_data *data, t_cmd *cmd)
{
	int		prev;

	prev = -1;
	while (cmd)
	{
		secured_pipe(data, cmd);
		cmd->pid = secured_fork(data);
		if (!cmd->pid)
		{
			open_files(data, cmd);
			check_access(data, cmd);
			exec_cmd(data, cmd, prev);
		}
		closer(1, prev);
		prev = dup(cmd->pfd[0]);
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		cmd = cmd->next;
	}
	close(prev);
	waiter(data, data->cmd_list);
}

//recieves all cmds. Forks if we have pipes or no build-ins.
void	start_exec(t_data *data)
{
	t_cmd	*cmd;

	data->envpath = set_path(data);
	cmd = data->cmd_list;
	if (cmd->cmd_arg && (cmd->next || !cmd->buildin))
		handle_pipes(data, cmd);
	else if (cmd->cmd_arg)
	{
		open_files(data, cmd);
		exec_cmd(data, cmd, 0);
	}
}
