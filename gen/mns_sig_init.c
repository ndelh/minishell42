/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_sig_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:12:04 by agamay            #+#    #+#             */
/*   Updated: 2025/03/31 16:12:21 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sigint_wait(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

static void	sigint_handler(int sig)
{
	write(1, "^C", 2);
	g_signal = sig;
	close(STDIN_FILENO);
}

//initialize signals for ^C(SIGINT(2)) and ^\(SIGQUIT(3)).
//0 for interractive mode. 1 for children. 2 for waiting parent.
void	signals_init(int type)
{
	if (type == 0)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);
	}
	else if (type == 2)
		signal(SIGINT, &sigint_wait);
	else if (type == 3)
		signal(SIGINT, SIG_IGN);
}
