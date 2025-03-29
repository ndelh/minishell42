#include "../minishell.h"

int	ft_isdigit_str(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (0);
		str++;
	}
	return (2048);
}

int	mns_exit(t_data *data, t_cmd *cmd)
{
	int	ret;
	int	valid;

	valid = 0;
	ret = data->exit;
	write(1, "exit\n", 5);
	if (cmd && cmd->cmd_arg && ft_isdigit_str(cmd->cmd_arg[1]))
	{
		ret = atoi(cmd->cmd_arg[1]);
		valid = 1;
	}
	else if (cmd && cmd->cmd_arg[1])
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		ret = 2;
	}
	if (cmd && cmd->cmd_arg && cmd->cmd_arg[valid + 1] && valid)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		ret = 1;
		if (!cmd->pid)
			return (ret);
	}
	ft_end(data);
	exit(ret % 256);
}
