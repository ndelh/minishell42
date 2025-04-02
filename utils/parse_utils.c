/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:02:27 by agamay            #+#    #+#             */
/*   Updated: 2025/04/02 16:11:11 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_char(char *s)
{
	while (*s && ft_isspace3(*s))
		s++;
	if (*s && *s == '|')
	{
		ft_putendl_fd("unexpected error near token `|'", 2);
		return (0);
	}
	return (1);
}
