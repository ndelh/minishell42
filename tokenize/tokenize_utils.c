/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:54:49 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/16 18:55:00 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sanitize(char *s)
{
	char	*end;
	char	*to_ret;

	while (*s && (*s == 32 || *s == '<' || *s == '>'))
		s++;
	end = s;
	while (*(end))
		end++;
	while (*(end - 1) == 32)
		end--;
	to_ret = ft_substr(s, 0, ft_strlen(s) - ft_strlen(end));
	return (to_ret);
}
