/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:22:49 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/29 14:46:00 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gen_name(void)
{
	char	*to_ret;
	char	*temp;
	int		fd;

	to_ret = malloc(sizeof(char) * 10);
	if (!to_ret)
		exit (0);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (0);
	read(fd, to_ret, 9);
	to_ret[9] = 0;
	if (ft_strchr(to_ret, '/'))
	{
		free(to_ret);
		to_ret = gen_name();
	}
	close(fd);
	temp = ft_strjoin("/tmp/", to_ret);
	free(to_ret);
	return (temp);
}

void	fill_heredoc(t_data *data, int fd, t_token *list, t_env *my_env)
{
	char	*line;
	int		nb;

	signals_init(2);
	line = readline(">");
	nb = 1;
	while (line != NULL && ft_strcmp(line, list->piece) && g_signal != SIGINT)
	{
		if (!list->h_no_expand)
			line = gen_expand_line(data, line, my_env, NULL);
		ft_putendl_fd(line, fd);
		free(line);
		nb++;
		line = readline(">");
	}
	if (line == NULL && g_signal != SIGINT)
		print_eof(nb, list->piece);
	if (g_signal == SIGINT)
		secured_dup2(data, data->standard_in, STDIN_FILENO);
	free(line);
	signals_init(0);
}

void	adjust_here_doc(t_data *data, t_token *list, t_env *my_env)
{
	char	*name;
	int		fd;

	name = gen_name();
	fd = open(name, O_WRONLY | O_CREAT, 0666);
	fill_heredoc(data, fd, list, my_env);
	close(fd);
	free(list->piece);
	list->piece = name;
}

void	run_redir_list(t_data *data, t_token *list, t_env *my_env)
{
	while (list)
	{
		if (list->type == HEREDOC && g_signal != SIGINT)
			adjust_here_doc(data, list, my_env);
		list = list->next;
	}
}

void	change_hdoc(t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		if (cmd->rdir_list)
			run_redir_list(data, cmd->rdir_list, data->my_env);
		cmd = cmd->next;
	}
}
