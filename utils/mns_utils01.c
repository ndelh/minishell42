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
		if (fd != -1)
			close(fd);
	}
	va_end(arg);
}

void	waiter(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		i = 1;//tmp for test

	while (cmd)
	{
		pid = waitpid(cmd->pid, &g_status, 0);
		if (pid == -1)
		{
			perror("waitpid failed");
			(void)data;
			// free_all(data);
			exit(EXIT_FAILURE);
		}
		printf("child %d exit code: %d\n", i++, g_status);//tmp for test
		cmd = cmd->next;
	}
}

void	secured_dup2(t_data *data, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2 failed");
		(void)data;
		// free_all(data);
		exit(EXIT_FAILURE);
	}
	(void)data;
}

void	secured_pipe(t_data *data, int pfd[2])
{
	if (pipe(pfd) == -1)
	{
		perror("pipe creation failed");
		(void)data;
		// free_all(data);
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
		(void)data;
		// free_all(data);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
