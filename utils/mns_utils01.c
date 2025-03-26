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

void	waiter(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		w_status;
	int		i = 1;//tmp for test

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
		printf("child %d wait code: %d\n", i++, w_status % 255);//tmp for test
		cmd = cmd->next;
	}
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
		signals_init(1);
	return (ret);
}
