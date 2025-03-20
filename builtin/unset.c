/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:21:35 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/19 20:20:36 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	relink_env(t_env *previous, t_env *next)
{
	if (previous)
	{
		previous->next = next;
		if (next)
			next->previous = previous;
	}
	if (next)
	{
		next->previous = previous;
		if (previous)
			previous->next = next;
	}
}

void	ft_unset(t_env **my_env, char *s)
{
	t_env	*cursor;
	t_env	*previous;
	t_env	*next;

	cursor = *my_env;
	while (cursor && ft_strncmp(cursor->name, s, strlen(s + 1)))
		cursor = cursor->next;
	if (cursor)
	{
		previous = cursor->previous;
		next = cursor->next;
		free(cursor->name);
		free(cursor->content);
		free(cursor);
		if (!previous)
			*my_env = next;
		relink_env(previous, next);
	}
	printf("%s\n", (*my_env)->name);
}

void	exec_unset(char **exe, t_data *data)
{
	exe++;
	while (*exe)
	{
		ft_unset(&data->my_env, *exe);
		exe++;
	}
}
