/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:57:50 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/17 17:05:34 by ndelhota         ###   ########.fr       */
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

void	print_complex_tab(char **s, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		printf("line number :%d %s\n", j, *s);
		j++;
		s++;
	}
}

void	free_complex_tab(char **s, int i)
{
	int		j;
	char	**to_free;

	to_free = s;
	j = 0;
	while (j < i)
	{
		free(*s);
		j++;
		s++;
	}
	free(*s);
	free(to_free);
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
