/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:32:23 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/03 15:17:37 by ndelhota         ###   ########.fr       */
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
	UNKNOW,
	D_QUOTE,
	S_QUOTE,
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
	char			*piece;
	int				cmd_num;
	t_type			type;

}	t_token;

typedef struct s_cmd
{
	struct s_cmd	*previous;
	struct s_cmd	*next;
	t_token	*pipe_list;
	t_token *redir_in;
	t_token	*redir_out;
}	t_cmd;

typedef struct s_data
{
	char	**my_env;
	t_token	*token_list;
}	t_data;


void	ft_gen(t_data **data, char **envp);
//utils 
void	ft_free_tab(char **tab);
void	ft_print_tab(char **tab);
void	ft_add_last(t_token **list, t_token *to_add);
void	ft_go_last(t_token **list);
int		tab_len(char **tab);
//tokenize
void	ft_tokenize(t_data *data, char *line);
char	**split_quote(char *s);
char	**split_at_char(char *s, char c);
void	first_sort(t_data *data, char **first_split);
void	gen_pipe_list(t_token **oldlist);
void	gen_redirection_line(t_token **oldlist);
void	restablish_link(t_token **cursor, t_token *p, t_token *n);
void	gen_new_chain(t_token **list, char **tab);
char	**split_at_redir(char *s);
//end
void	free_token_list(t_token *to_free);
void	ft_end(t_data *data);
#endif
