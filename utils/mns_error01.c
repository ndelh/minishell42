#include "../minishell.h"

//if open==-1, displays right error and return
void	redir_error(t_data *data, t_cmd *cmd, t_token *rdir_list)
{
	perror(rdir_list->piece);
	if (!cmd->pid)
	{
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		ft_end(data);
		exit(1);
	}
	g_status = 1;
}

//if cmd is a dir, displays right error and return
void	isdir_error(t_data *data, t_cmd *cmd)
{
	errno = EISDIR;
	perror(cmd->cmd_arg[0]);
	if (!cmd->pid)
	{
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		ft_end(data);
		exit(126);
	}
	g_status = 126;
}

//if cmd not found, displays the right error and return
void	fct_error(t_data *data, t_cmd *cmd)
{
	perror(cmd->cmd_arg[0]);
	if (!cmd->pid)
	{
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		ft_end(data);
		exit(127);
	}
	g_status = 127;
}
