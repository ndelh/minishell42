#include "../minishell.h"

void	sigint_handler(int sig)
{
	write(1, "^C", 2);
	g_signal = sig;
	close(STDIN_FILENO);
}

//initialize signals for ^C(SIGINT(2)) and ^\(SIGQUIT(3)).
//0 for interractive mode. 1 for children. 2 for waiting parent.
void	signals_init(int type)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	if (type == 0)
	{
		sa_int.sa_handler = &sigint_handler;
		sa_quit.sa_handler = SIG_IGN;
	}
	else if (type == 1)
	{
		sa_int.sa_handler = SIG_DFL;
		sa_quit.sa_handler = SIG_DFL;
	}
	else if (type == 2)
	{
		sa_int.sa_handler = SIG_IGN;
		sa_quit.sa_handler = SIG_IGN;
	}
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, 0))
		perror("SIGINT init failed.");
	if (sigaction(SIGQUIT, &sa_quit, 0))
		perror("SIGQUIT init failed.");
}
