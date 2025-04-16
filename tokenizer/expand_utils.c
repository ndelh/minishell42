/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:37:17 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/16 13:01:51 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_expand(char *name, t_line *line)
{
	t_line	*stoppage;

	stoppage = line->end_expand->next;
	line = line->next;
	while (*name && line)
	{
		if (*name == line->letter)
		{
			name++;
			line = line->next;
		}
		else
			break ;
	}
	if (line != stoppage || *name)
		return (0);
	else
		return (1);
}

t_env	*find_env_node(t_env *env, t_line *line)
{
	while (env)
	{
		if (match_expand(env->name, line))
			break ;
		env = env->next;
	}
	return (env);
}

void	find_end_expand(t_line **line)
{
	t_line	*reminder;

	reminder = *line;
	*line = (*line)->next;
	if ((*line)->letter == '?' || ft_isdigit((*line)->letter))
	{
		reminder->end_expand = *line;
		return ;
	}
	if (*line)
	{
		while ((*line)->next && (ft_isalnum((*line)->next->letter)
				|| (*line)->next->letter == '_'))
			*line = (*line)->next;
	}
	reminder->end_expand = *line;
}

int	seek_expand_end_cmd(t_line *line)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line->type == S_QUOTE)
			line = line->end_quote->next;
		else if (line && (line->letter == '$'))
		{
			if (line->next && !is_white_space(line->next->letter))
			{
				find_end_expand(&line);
				i++;
			}
		}
		if (line)
			line = line->next;
	}
	return (i);
}
