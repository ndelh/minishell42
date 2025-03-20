#include "../minishell.h"

//sets the args for execve if absolute path is given.
static void	abs_path(t_cmd *cmd)
{
	char	*tmp;
	int		len;

	cmd->cmd_path = cmd->cmd_arg[0];
	len = ft_strrchr(cmd->cmd_arg[0], '/') - cmd->cmd_arg[0] + 1;
	tmp = ft_substr(cmd->cmd_arg[0], len, ft_strlen(cmd->cmd_arg[0]) - len);
	cmd->cmd_arg[0] = tmp;
}

//takes a char* and returns: 0 for an X_OK file, 1 for a dir, -1 for error.
static int	check_nature(t_data *data, t_cmd *cmd, char *cmd_path)
{
	struct stat	st_buff;

	st_buff.st_mode = -1;
	stat(cmd_path, &st_buff);
	if (S_ISDIR(st_buff.st_mode))
		isdir_error(data, cmd);
	if (!access(cmd_path, X_OK))
		return (0);
	return (-1);
}

//checks if the first arg of cmd->cmd_arg exists, and it's nature.
void	check_access(t_data *data, t_cmd *cmd)
{
	char	*cmd_path;
	int		i;

	i = -1;
	while (data->envpath[++i])
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
	fct_error(data, cmd);
}

//finds PATH in env, puts it in a char** for easy use.
char	**set_path(t_data *data)
{
	t_env	*envlst;
	char	**path;

	envlst = data->my_env;
	path = NULL;
	while (envlst && ft_strncmp("PATH", envlst->name, 4))
		envlst = envlst->next;
	if (envlst)
		path = ft_split(envlst->content, ':');
	return (path);
}

void	call_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_arg[0], "export"))
		ft_export(data, cmd);
	else
		return ;
	// if (cmd->cmd_arg[0] == unset)
	// 	unset();
}
