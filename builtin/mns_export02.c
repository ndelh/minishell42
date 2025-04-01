/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_export02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:11:28 by agamay            #+#    #+#             */
/*   Updated: 2025/04/01 11:11:31 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//prints env new->contents in ascii order.
void	exp_printenv(t_env *env, t_env *tmp, char *printed, int len)
{
	t_env	*to_print;

	to_print = tmp;
	while (len--)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, to_print->name) < 0
				&& ft_strcmp(tmp->name, printed) > 0)
				to_print = tmp;
			else if (ft_strcmp(to_print->name, printed) <= 0)
				to_print = tmp;
			tmp = tmp->next;
		}
		if (ft_strcmp(to_print->name, "_"))
		{
			printf("declare -x %s", to_print->name);
			if (to_print->content)
				printf("=\"%s\"", to_print->content);
			printf("\n");
		}
		printed = to_print->name;
		tmp = env;
	}
}

//checks if arg is valid.
int	exp_isvalid(t_data *data, char *arg)
{
	char	*tmp;

	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(*arg) && *arg != '_')
	{
		export_error(data, arg);
		return (0);
	}
	tmp = arg;
	while (*tmp && *tmp != '=' && *tmp != '+')
	{
		if (!ft_isalnum(*tmp) && *tmp != '_')
		{
			export_error(data, arg);
			return (0);
		}
		tmp++;
	}
	return (1);
}
