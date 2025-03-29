#include "../minishell.h"

void	sig_hdoc_handler(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = sig;
	close(STDIN_FILENO);
}

void	sigint_handler(int sig)
{
	static int i = 0;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	// printf("singint_main: %d\n", i++);
	rl_redisplay();
	g_signal = sig;
}

//initialize signals for ^C(SIGINT(2)) and ^\(SIGQUIT(3)).
void	signals_init(int type)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	if (type == 1)
	{
		sa_int.sa_handler = SIG_DFL;
		sa_quit.sa_handler = SIG_DFL;
	}
	else if (type == 0)
	{
		sa_int.sa_handler = &sigint_handler;
		sa_quit.sa_handler = SIG_IGN;
	}
	if (type == 2)
	{
		sa_int.sa_handler = &sig_hdoc_handler;
		sa_quit.sa_handler = SIG_IGN;
	}
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, 0))
		perror("SIGINT init failed.");
	if (sigaction(SIGQUIT, &sa_quit, 0))
		perror("SIGQUIT init failed.");
}
