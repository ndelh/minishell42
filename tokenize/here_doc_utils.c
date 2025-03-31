/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:33:34 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/27 20:43:24 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_eof(int nb, char *limiter)
{
	printf("warning : here_document at line %d ", nb);
	printf("delimited by end of file (wanted '%s')\n", limiter);
}

void	modulate_line(t_data *data, char **line, t_env *my_env)
{
	char	*to_ret;

	to_ret = gen_expand_line(data, *line, my_env, NULL);
	free(*line);
	*line = to_ret;
}

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
