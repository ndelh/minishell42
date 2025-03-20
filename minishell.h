/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:32:23 by ndelhota          #+#    #+#             */
/*   Updated: 2025/03/20 09:47:32 by ndelhota         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>

extern int	g_status;

typedef enum type_e
{
	UNKNOW,
	D_QUOTE,
	S_QUOTE,
	REDIR,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE
}	t_type;

typedef struct s_token
{
	struct s_token	*previous;
	struct s_token	*next;
	char			*piece;
	int				fd;
	t_type			type;
	struct s_token	*block_end;

}	t_token;

typedef struct s_cmd
{
	struct s_cmd	*previous;
	struct s_cmd	*next;
	char			**cmd_arg;
	int				tab_line;
	char			*cmd_path;
	pid_t			pid;
	int				buildin;
	t_token			*current_cmd;
	t_token			*rdir_list;
}	t_cmd;

typedef struct s_env
{
	struct s_env	*previous;
	struct s_env	*next;
	char			*name;
	char			*content;
	int				status;
}	t_env;

typedef struct s_data
{
	t_env		*my_env;
	char		**envpath;
	t_token		*token_list;
	t_cmd		*cmd_list;
	char		**envp;
	int			standard_in;
	int			standard_out;
}	t_data;

void	ft_gen(t_data **data, char **envp);
void	ft_dup_std(t_data *data);
char	**convert_envp(t_env *my_env);
//utils 
void	ft_free_tab(char **tab);
void	ft_print_tab(char **tab);
void	free_complex_tab(char **s, int i);
void	print_complex_tab(char **s, int i);
void	ft_add_last(t_token **list, t_token *to_add);
void	ft_go_last(t_token **list);
int		tab_len(char **tab);
t_env	*env_lstnew(char *name, char *content);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
char	*sanitize(char *s);
void	closer(int count, ...);
void	waiter(t_data *data, t_cmd *cmd);
void	secured_dup2(t_data *data, int fd1, int fd2);
void	secured_pipe(t_data *data, int pfd[2]);
pid_t	secured_fork(t_data *data);
//tokenize
int		is_incomplete(char *s);
int		count_expand_line(char *s, t_env *env);
int		count_expand_split(char *s);
int		check_expand(char *s);
int		redir_alone(char *s);
int		global_len(t_token *list, t_token *stoppage);
void	replace_expand(char **tab, t_env *env);
void	free_complex_tab(char **tab, int i);
void	ft_tokenize(t_data *data, char *line);
void	create_cmd_list(t_data *data, t_token *to_shatter);
char	**split_quote(char *s);
char	*ft_mend_line(char **tab, int i);
char	**isolate_expand(char *s, int i);
char	**split_at_char(char *s, char c);
char	*gen_expand_line(char *s, t_env *env);
void	first_sort(t_data *data, char **first_split);
void	gen_pipe_list(t_token **oldlist);
void	gen_redirection_line(t_token **oldlist);
void	restablish_link(t_token **cursor, t_token *p, t_token *n);
void	gen_new_chain(t_token **list, char **tab);
t_token	*arrange_head(t_token *head, t_token *old_p, t_token *old_n);
void	seek_block(t_cmd *list);
void	sort_redir_exe(t_cmd *list);
void	arrange_tail(t_token **cursor, t_token *old_p, t_token *old_n);
char	**split_at_redir(char *s);
void	expand_in_list(t_cmd *cmd, t_data *data);
void	convert_cmd_list(t_cmd *cmd);
void	multiple_complex_line(t_token *list, t_cmd *cmd, int *i);
void	one_complex_line(t_token **list, t_cmd *cmd, int *i);
void	convert_redir_list(t_cmd *cmd);
void	change_hdoc(t_cmd *cmd, t_data *data);
//end
void	free_token_list(t_token *to_free, int i);
void	free_env_list(t_env *env);
void	free_cmd_list(t_cmd *to_free);
void	ft_end(t_data *data);
//error management
void	redir_error(t_data *data, t_cmd *cmd, t_token *redirlst);
void	isdir_error(t_data *data, t_cmd *cmd);
void	fct_error(t_data *data, t_cmd *cmd);
//signals
void	signals_init(void);
void	sig_handler(int sig);
//exec
void	start_exec(t_data *data);
void	check_access(t_data *data, t_cmd *cmd);
char	**set_path(t_data *data);
void	call_builtin(t_data *data, t_cmd *cmd);
//builtins
int		ft_export(t_data *data, t_cmd *cmd);
void	exec_unset(char **exe, t_data *data);

#endif
