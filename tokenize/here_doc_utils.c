/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:33:34 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/27 20:43:24 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_eof(int nb, char *limiter)
{
	printf("warning : here_document at line %d ", nb);
	printf("delimited by end of file (wanted '%s')\n", limiter);
}

