/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:22:49 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/17 14:41:43 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gen_valid_name(t_data *data)
{
	int		try;
	int		fd;
	char	*to_ret;

	try = 0;
	to_ret = NULL;
	while (try < 1000)
	{
		to_ret = gen_name();
		if (!to_ret)
			mns_exit(data, NULL);
		fd = open(to_ret, O_CREAT | O_WRONLY, 0666);
		if (fd != -1)
		{
			close(fd);
			return (to_ret);
		}
		free(to_ret);
		to_ret = NULL ;
		try++;
	}
	mns_exit(data, NULL);
	return (NULL);
}

void	fill_heredoc(t_data *data, int fd, t_token *list)
{
	char	*line;
	int		nb;
	t_line	*line_list;

	line = readline(">");
	nb = 1;
	while (line != NULL && ft_strcmp(line, list->piece) && g_signal != SIGINT)
	{
		line_list = gen_list(line, data);
		if (!list->h_no_expand)
			line_list = expand_in_redir(data, line_list);
		write_in_hdoc(line_list, fd);
		free_line_list(&line_list);
		free(line);
		nb++;
		line = readline(">");
	}
	if (line == NULL && g_signal != SIGINT)
		print_eof(data->line_hdoc, list->piece);
	if (g_signal == SIGINT)
		secured_dup2(data, data->standard_in, STDIN_FILENO);
	free(line);
	data->line_hdoc += nb;
}

void	adjust_here_doc(t_data *data, t_token *list)
{
	char	*name;
	int		fd;
	t_env	*my_env;

	my_env = data->my_env;
	name = gen_valid_name(data);
	fd = open(name, O_WRONLY | O_CREAT, 0666);
	fill_heredoc(data, fd, list);
	close(fd);
	free(list->piece);
	list->piece = name;
}

void	run_redir_list(t_data *data, t_cmd *cmd)
{
	t_token	*list;

	list = cmd->rdir_list;
	while (list)
	{
		if (list->type == HEREDOC && g_signal != SIGINT)
			adjust_here_doc(data, list);
		list = list->next;
	}
}

void	change_hdoc(t_cmd *cmd, t_data *data)
{
	data->line_hdoc = 1;
	while (cmd)
	{
		if (cmd->rdir_list)
			run_redir_list(data, cmd);
		cmd = cmd->next;
	}
}
