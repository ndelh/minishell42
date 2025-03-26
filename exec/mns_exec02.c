#include "../minishell.h"

//sets the args for execve if absolute path is given.
void	abs_path(t_cmd *cmd)
{
	char	*tmp;
	int		len;

	cmd->cmd_path = cmd->cmd_arg[0];
	len = ft_strrchr(cmd->cmd_arg[0], '/') - cmd->cmd_arg[0] + 1;
	tmp = ft_substr(cmd->cmd_arg[0], len, ft_strlen(cmd->cmd_arg[0]) - len);
	cmd->cmd_arg[0] = tmp;
}

//takes a char* and returns: 0 for an X_OK file, 1 for a dir, -1 for error.
int	check_nature(t_data *data, t_cmd *cmd, char *cmd_path)
{
	struct stat	st_buff;

	st_buff.st_mode = -1;
	stat(cmd_path, &st_buff);
	if (**(cmd->cmd_arg) && S_ISDIR(st_buff.st_mode))
	{
		free(cmd_path);
		isdir_error(data, cmd);
	}
	if (**(cmd->cmd_arg) && !access(cmd_path, X_OK))//band-aid. why cans access(X_OK) a "" arg?
		return (0);
	return (-1);
}

//finds PATH in env, puts it in a char** for easy use.
char	**set_path(t_data *data)
{
	t_env	*envlst;
	char	**path;

	envlst = data->my_env;
	path = NULL;
	ft_free_tab(data->envpath);
	while (envlst && ft_strncmp("PATH", envlst->name, 4))
		envlst = envlst->next;
	if (envlst)
		path = ft_split(envlst->content, ':');
	return (path);
}

//calls the right builtin fct.
static void	call_builtin(t_data *data, t_cmd *cmd)
{
	if (!cmd->cmd_arg)
		return ;
	if (!ft_strncmp(cmd->cmd_arg[0], "export", 6))
		mns_export(data, cmd);
	else if (!ft_strncmp(cmd->cmd_arg[0], "unset", 5))
		exec_unset(cmd->cmd_arg, data);
	else if (!ft_strncmp(cmd->cmd_arg[0], "env", 3))
		mns_env(data);
	else if (!ft_strncmp(cmd->cmd_arg[0], "echo", 4))
		mns_echo(cmd);
	else if (!ft_strncmp(cmd->cmd_arg[0], "exit", 4))
		mns_exit(data, cmd);
}

void	call_or_exec(t_data *data, t_cmd *cmd)
{
	if (cmd->buildin || !cmd->cmd_arg)
	{
		call_builtin(data, cmd);
		secured_dup2(data, data->standard_in, 0);
		secured_dup2(data, data->standard_out, 1);
		if (cmd->previous || cmd->next)
		{
			ft_end(data);
			exit(0);
		}
	}
	else if (cmd->cmd_arg)
	{
		execve(cmd->cmd_path, cmd->cmd_arg, data->envp);
		perror("execve failed");
		ft_end(data);
		exit(127);
	}
	else
	{
		ft_end(data);
		exit(0);
	}
}
