/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:50:53 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/23 15:27:45 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(t_data *data)
{
	char	*to_ret;

	data = NULL;
	to_ret = malloc(sizeof(char) * 4096);
	if (!to_ret)
		ft_end(data);
	if (!getcwd(to_ret, 4096))
	{
		free(to_ret);
		perror("pwd");
		to_ret = NULL;
	}
	return (to_ret);
}

void	exec_pwd(t_data *data)
{
	char	*to_print;

	to_print = get_pwd(data);
	printf("%s\n", to_print);
	free(to_print);
}
