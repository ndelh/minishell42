/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:45:49 by agamay            #+#    #+#             */
/*   Updated: 2025/04/17 16:24:00 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_access(t_data *data, char *cmd)
{
	int		i;
	char	*ret;

	i = -1;
	while (data->envpath && data->envpath[++i])
	{
		ret = ft_vastrjoin(3, data->envpath[i], "/", cmd);
		if (!access(ret, X_OK))
			return (ret);
		free(ret);
	}
	ret = ft_strdup(cmd);
	return (ret);
}

//takes last arg from last fct, puts it in "_" value.
void	assign_(t_data *data)
{
	t_env	*us;
	char	*us_n;
	char	*us_c;
	t_cmd	*cmd;
	int		len;

	cmd = (t_cmd *)ft_lstlast((t_list *)data->cmd_list);
	if (!cmd->cmd_arg || !*(cmd->cmd_arg))
		return ;
	len = tab_len(cmd->cmd_arg);
	if (!cmd->buildin && len == 1)
		us_c = check_access(data, cmd->cmd_arg[0]);
	else
		us_c = ft_strdup(cmd->cmd_arg[len - 1]);
	us = go_to_env_node(data->my_env, "_");
	if (!us)
	{
		us_n = strdup("_");
		env_lstadd_back(&data->my_env, env_lstnew(us_n, us_c, 1));
	}
	else
	{
		free(us->content);
		us->content = us_c;
	}
}

//prints env.
int	mns_env(t_data *data, t_cmd *cmd)
{
	t_env	*envlst;

	envlst = data->my_env;
	if (cmd->cmd_arg[1])
		return (1);
	while (envlst)
	{
		if (envlst->status)
			printf("%s=%s\n", envlst->name, envlst->content);
		envlst = envlst->next;
	}
	return (0);
}
