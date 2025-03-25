/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:07:20 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 10:11:09 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*go_to_env_node(t_env *list, char *s)
{
	while (list && ft_strncmp(s, list->name, ft_strlen(s) + 1))
		list = list->next;
	return (list);
}
