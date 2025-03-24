/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:48:56 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/22 17:54:19 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_with_space(char *s1, char *s2)
{
	char	*to_ret;
	int		total_len;

	total_len = (ft_strlen(s1) + ft_strlen(s2) + 2);
	to_ret = ft_calloc(sizeof(char), total_len);
	if (!to_ret)
		return (NULL);
	ft_strlcat(to_ret, s1, total_len);
	ft_strlcat(to_ret, " ", total_len);
	ft_strlcat(to_ret, s2, total_len);
	free(s1);
	free(s2);
	return (to_ret);
}

char	*space_strchr(char *s)
{
	if (!s || !*s)
		return (NULL);
	while (*s && !is_space(*s))
		s++;
	if (*s)
		return (s);
	else
		return (NULL);
}
