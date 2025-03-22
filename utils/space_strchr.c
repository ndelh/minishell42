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
