/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:45:57 by agamay            #+#    #+#             */
/*   Updated: 2025/03/31 16:46:04 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_islong(char *str)
{
	long long int	nb;
	long long int	neg;

	nb = 0;
	neg = 1;
	while ((*str == 32) || (*str <= 13 && *str >= 9))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while ((*str) && (*str >= '0' && (*str <= '9')))
	{
		nb = (nb * 10 + (*str - 48));
		if (nb * neg > INT_MAX || nb * neg < INT_MIN)
			return (0);
		str++;
	}
	return (2048);
}

static int	ft_isdigit_str(char *str)
{
	int		ret;
	char	*tmp;

	tmp = str;
	if (!tmp)
		return (0);
	while (ft_isspace3(*tmp))
		tmp++;
	if (*tmp == '+' || *tmp == '-')
		tmp++;
	while (*tmp)
	{
		if (!(*tmp <= '9' && *tmp >= '0'))
			return (0);
		tmp++;
	}
	ret = ft_islong(str);
	return (ret);
}

static int	check_args(t_cmd *cmd, int ret, int *valid)
{
	if (cmd && cmd->cmd_arg && ft_isdigit_str(cmd->cmd_arg[1]))
	{
		ret = atoi(cmd->cmd_arg[1]);
		*valid = 1;
	}
	else if (cmd && cmd->cmd_arg[1])
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		ret = 2;
	}
	return (ret);
}

//will exit process with last exit code,
//or given numeric argument.
int	mns_exit(t_data *data, t_cmd *cmd)
{
	int	ret;
	int	valid;

	valid = 0;
	ret = data->exit;
	ret = ret % 255;
	write(1, "exit\n", 5);
	ret = check_args(cmd, ret, &valid);
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
