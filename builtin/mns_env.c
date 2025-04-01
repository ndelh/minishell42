/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:45:49 by agamay            #+#    #+#             */
/*   Updated: 2025/03/31 16:45:50 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
