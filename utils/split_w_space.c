/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_w_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:59:34 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/22 17:03:36 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	else
		return (0);
}

int	count_w(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s)
			count++;
		while (*s && !is_space(*s))
			s++;
	}
	return (count);
}

void	move_all(char **s, char **cursor)
{
	while (**s && is_space(**s))
		(*s)++;
	*cursor = *s;
	while (**cursor && !is_space(**cursor))
		(*cursor)++;
}

char	**split_w_space(char *s)
{
	int		count;
	char	**split;
	char	*cursor;
	int		j;

	j = 0;
	count = count_w(s);
	printf("count : %d\n", count);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	while (j < count)
	{
		move_all(&s, &cursor);
		split[j] = ft_substr(s, 0, ft_strlen(s) - ft_strlen(cursor));
		if (!split[j])
			return (NULL);
		s = cursor;
		j++;
	}
	split[j] = NULL;
	return (split);
}
