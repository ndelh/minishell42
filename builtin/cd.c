/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:08:15 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/21 17:01:21 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fetch_node(t_env **pwd, t_env **old_pwd, t_data *data, char *s)
{
	*pwd = go_to_env_node(data->my_env, "PWD");
	*old_pwd = go_to_env_node(data->my_env, "OLDPWD");
	if (*old_pwd)
	{
		free((*old_pwd)->content);
		(*old_pwd)->content = s;
	}
	else
		free(s);
	if (*pwd)
	{
		free((*pwd)->content);
		(*pwd)->content = get_pwd(data);
	}
}

static int	fetch_cd(char *s, t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*current_pwd;

	pwd = NULL;
	old_pwd = NULL;
	current_pwd = get_pwd(data);
	if (!chdir(s))
		fetch_node(&pwd, &old_pwd, data, current_pwd);
	else
	{
		free(current_pwd);
		perror("chdir");
		return (1);
	}
	return (0);
}

int	exec_cd(char **tab, t_data *data)
{
	int	ret;

	if (tab_len(tab) == 1)
		return (1);
	else if (tab_len(tab) > 2)
	{
		ft_putstr_fd("too_many_args\n", 2);
		return (1);
	}
	tab++;
	ret = fetch_cd(*tab, data);
	return (ret);
}
