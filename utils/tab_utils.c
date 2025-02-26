/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:57:50 by ndelhota          #+#    #+#             */
/*   Updated: 2025/02/26 12:13:55 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	char	**temp;

	if (!tab)
		return ;
	temp = tab;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(*tab);
	free(temp);
}

void	ft_print_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		printf("%s\n", *tab);
		tab++;
	}
}

int	tab_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (*tab)
	{
		i++;
		tab++;
	}
	return (i);
}
