#include "../minishell.h"

void	mns_exit(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (cmd && cmd->cmd_arg[1])
		ret = atoi(cmd->cmd_arg[1]);
	else
		ret = g_status;
	ft_end(data);
	write(1, "exit\n", 5);
	// ft_putnbr_fd(ret % 255, 2);//temp
	exit (ret % 255);//should be %256
}
