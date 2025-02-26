/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:32:23 by ndelhota          #+#    #+#             */
/*   Updated: 2025/02/26 13:23:55 by ndelhota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"

typedef enum type_e
{
	d_quote,
	s_quote,
	PIPE,
	word,
	infiling,
	outfiling,
	heredoc
}	t_type;

typedef struct s_token
{
	struct s_token	*previous;
	struct s_token	*next;
	t_type			type;

}	t_token;

typedef struct s_data
{
	char	**my_env;
}	t_data;

void	ft_gen(t_data **data, char **envp);

//utils 
void	ft_free_tab(char **tab);
void	ft_print_tab(char **tab);
int		tab_len(char **tab);
//tokenize
void	ft_tokenize(t_data *data, char *line);
char	**split_quote(char *s);
//end
void	ft_end(t_data *data);
#endif
