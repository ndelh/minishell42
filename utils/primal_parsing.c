/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primal_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:59 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/25 13:22:48 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_end_pipe(char *s)
{
	int	test;

	test = 1;
	while (*s)
	{
		if (*s == '|')
			test = 0;
		s++;
	}
	if (test == 0)
	{
		s--;
		while (is_space(*s) || (*s >= 9 && *s <= 13))
			s--;
		if (*s != '|')
			test = 1;
	}
	if (test == 0)
		printf("syntax error near unexpected token |\n");
	return (test);
}

int	check_incomplete_redir(char *s)
{
	char	a;
	
	if (*s == '<')
		a = '>';
	else
		a = '<';
	s++;
	if (*s == *(s - 1))
		s++;
	while (*s && (is_space(*s) && *s != a))
		s++;
	if (!*s || *s == '|' || *s == '<' || *s == '>')
	{
		printf("uncomplete redir\n");
		return (0);
	}
	return (1);
}

int	check_closed_quote(char **s)
{
	char	a;

	a = **s;
	(*s)++;
	while (**s && **s != a)
		(*s)++;
	if (!**s)
	{
		printf("unclosed quote : %c\n", a);
		return (0);
	}
	(*s)++;
	return (1);
}

int	primal_parse(char *s)
{
	if (!*s || !check_end_pipe(s))
		return (0);
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			if (!check_closed_quote(&s))
				return (0);
		}
		else if (*s == '<' || *s == '>')
		{
			if (!check_incomplete_redir(s))
				return (0);
			else
				s++;
		}
		else
			s++;
	}
	return (1);
}
