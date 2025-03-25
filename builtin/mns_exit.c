#include "../minishell.h"

int	mns_exit(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (cmd && cmd->cmd_arg[2])
	{
		errno = E2BIG;
		perror("exit");
		if (!cmd->previous && !cmd->next)
			return (1);
		else
		{
			ft_end(data);
			exit(1);
		}
	}
	else if (cmd && cmd->cmd_arg[1])
		ret = atoi(cmd->cmd_arg[1]);
	else
		ret = data->exit;
	ft_end(data);
	write(1, "exit\n", 5);
	exit(ret % 256);
}
