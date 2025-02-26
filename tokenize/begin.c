/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:53 by ndelhota          #+#    #+#             */
/*   Updated: 2025/02/26 13:43:30 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenize(t_data *data, char *line)
{
	char	**first_split;

	first_split = split_quote(line);
	ft_print_tab(first_split);
	ft_free_tab(first_split);
	data = NULL;
}
