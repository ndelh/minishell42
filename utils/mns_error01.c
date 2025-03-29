#include "../minishell.h"

//if open==-1, displays right error and return
void	redir_error(t_data *data, t_cmd *cmd, t_token *rdir_list)
{
	perror(rdir_list->piece);
	free_token_list(cmd->rdir_list, 0);
	cmd->rdir_list = NULL;
	if (cmd->pid == 1)
	{
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		ft_end(data);
		exit(1);
	}
	data->exit = 1;
}

//if cmd is a dir, displays right error and return
void	isdir_error(t_data *data, t_cmd *cmd)
{
	errno = EISDIR;
	perror(cmd->cmd_arg[0]);
	free_token_list(cmd->rdir_list, 0);
	cmd->rdir_list = NULL;
	if (cmd->pid == 1)
	{
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		ft_end(data);
		exit(126);
	}
	data->exit = 126;
}

//if cmd not found, displays the right error and return
void	fct_error(t_data *data, t_cmd *cmd)
{
	perror(cmd->cmd_arg[0]);
	free_token_list(cmd->rdir_list, 0);
	cmd->rdir_list = NULL;
	if (cmd->pid == 1)
	{
		closer(2, cmd->pfd[0], cmd->pfd[1]);
		ft_end(data);
		exit(127);
	}
	data->exit = 127;
}

void	export_error(t_data *data, char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->exit = 1;
}
