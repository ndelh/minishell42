/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:22:49 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/17 16:59:09 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gen_name(void)
{
	char	*to_ret;
	char	*temp;
	int		fd;

	to_ret = malloc(sizeof(char) * 16);
	if (!to_ret)
		exit (0);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (0);
	read(fd, to_ret, 15);
	to_ret[15] = 0;
	if (ft_strchr(to_ret, '/'))
	{
		free(to_ret);
		to_ret = gen_name();
	}
	close(fd);
	temp = ft_strjoin("/var/tmp/", to_ret);
	free(to_ret);
	return (temp);
}

void	fill_heredoc(int fd, char *limiter, t_env *my_env)
{
	char	*line;

	line = readline(">");
	while (ft_strncmp(line, limiter, ft_strlen(line + 1)))
	{
		line = gen_expand_line(line, my_env);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	free(line);
}

void	adjust_here_doc(t_token *list, t_env *my_env)
{
	char	*name;
	int		fd;

	name = gen_name();
	fd = open(name, O_WRONLY | O_CREAT, 0666);
	fill_heredoc(fd, list->piece, my_env);
	close(fd);
	free(list->piece);
	list->piece = name;
}

void	run_redir_list(t_token *list, t_env *my_env)
{
	while (list)
	{
		if (list->type == HEREDOC)
		{
			adjust_here_doc(list, my_env);
		}
		list = list->next;
	}
}

void	change_hdoc(t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		if (cmd->rdir_list)
			run_redir_list(cmd->rdir_list, data->my_env);
		cmd = cmd->next;
	}
}
