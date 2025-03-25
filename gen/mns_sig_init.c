#include "../minishell.h"

/*
//Exit success or no command given, ^D
exit(0);
//!, $>cmd identifier, "<cmd>: 'identifier': not a valid identifier"
exit(1);
//syntax error "syntax error near unexpected token 'cmd'"
exit(2);
//directory/file issue?
exit(126);
//command not found "<cmd>: command not found"
exit(127);
//^C SIGINT(2)
exit(130);
//^\ SIGQUIT(3)
exit(131);
//^z SIGTSTP(20)
exit(148);
//exit x
exit(x % 255);
*/

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = sig;
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1,"  \b\b", 4);
		g_signal = sig;
	}
}

//initialize signals for ^C(SIGINT(2)) and ^\(SIGQUIT(3)).
void	signals_init(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, 0))
		perror("SIGINT init failed.");
	if (sigaction(SIGQUIT, &sa, 0))
		perror("SIGQUIT init failed.");
}
