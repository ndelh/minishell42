#include "../minishell.h"

void	mns_echo(t_cmd *cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (cmd->cmd_arg[1] && !ft_strncmp(cmd->cmd_arg[1], "-n", 2))
	{
		i++;
		n++;
	}
	while (cmd->cmd_arg[i])
	{
		ft_putstr_fd(cmd->cmd_arg[i], 1);
		if (cmd->cmd_arg[++i])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}
