/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primal_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:59 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/02 16:18:11 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_succesive_pipe(char *s)
{
	while (*s)
	{
		if (*s == '|')
		{
			s++;
			while (*s && ft_isspace3(*s))
				s++;
			if (*s && *s == '|')
			{
				ft_putendl_fd("syntax error near unexpected token `|'", 2);
				return (0);
			}
		}
		s++;
	}
	return (1);
}

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
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
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
		ft_putendl_fd("incomplete redirection", 2);
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
		if (a == '\'')
			ft_putendl_fd("unclosed quote: `'`", 2);
		else
			ft_putendl_fd("unclosed quote: `\"`", 2);
		return (0);
	}
	(*s)++;
	return (1);
}

int	primal_parse(char *s)
{
	if (!s || !*s || !check_end_pipe(s) || !check_succesive_pipe(s))
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
