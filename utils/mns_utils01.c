/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:32:08 by agamay            #+#    #+#             */
/*   Updated: 2025/03/31 17:32:17 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//close multiple fds
void	closer(int count, ...)
{
	va_list	arg;
	int		fd;

	va_start(arg, count);
	while (count--)
	{
		fd = va_arg(arg, int);
		if (fd > 2)
			close(fd);
	}
	va_end(arg);
}

//waits for children in order of creation.
//gets wait statuses and set data->exit accordingly.
int	waiter(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		w_status;

	while (cmd)
	{
		pid = waitpid(cmd->pid, &w_status, 0);
		if (pid == -1)
		{
			perror("waitpid failed");
			ft_end(data);
			exit(EXIT_FAILURE);
		}
		if (WIFSIGNALED(w_status))
			data->exit = 128 + WTERMSIG(w_status);
		else
			data->exit = w_status;
		cmd = cmd->next;
	}
	signals_init(0);
	if (data->exit == 131)
		write(1, "Quit\n", 5);
	return (w_status);
}

void	secured_dup2(t_data *data, int fd1, int fd2)
{
	if (fd1 == -1 || fd2 == -1 || fd1 == fd2)
		return ;
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2 failed");
		ft_end(data);
		exit(EXIT_FAILURE);
	}
}

void	secured_pipe(t_data *data, t_cmd *cmd)
{
	if (pipe(cmd->pfd) == -1)
	{
		perror("pipe creation failed");
		ft_end(data);
		exit(EXIT_FAILURE);
	}
	(void)data;
}

pid_t	secured_fork(t_data *data)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
	{
		perror("fork failed");
		ft_end(data);
		exit(EXIT_FAILURE);
	}
	if (!ret)
	{
		signals_init(1);
		ret = 1;
	}
	else
		signals_init(2);
	return (ret);
}
