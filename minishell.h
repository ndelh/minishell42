/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:32:23 by ndelhota          #+#    #+#             */
/*   Updated: 2025/04/15 18:20:04 by ndelhota         ###   ########.fr       */
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
# include <limits.h>

extern int	g_signal;

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
	int				h_no_expand;
	struct s_token	*block_end;

}	t_token;

typedef struct s_cmd
{
	struct s_cmd	*previous;
	struct s_cmd	*next;
	struct s_line	*cmd_line;
	struct s_line	*redir_line;
	char			**cmd_arg;
	int				tab_line;
	char			*cmd_path;
	pid_t			pid;
	int				buildin;
	int				pfd[2];
	t_token			*current_cmd;
	t_token			*rdir_list;
	int				h_expand;
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
	int			line_hdoc;
	int			no_exec;
	int			exit;
}	t_data;

typedef	struct s_line
{
	char	letter;
	t_type	type;
	t_type	redir_type;
	int	wr;
	int	cmd_number;
	struct s_line	*end_quote;
	struct s_line	*end_redir;
	struct s_line	*end_expand;
	struct s_line	*previous;
	struct s_line	*next;
}	t_line;

int		primal_parse(char *s);
void	ft_gen(t_data **data, char **envp);
void	ft_dup_std(t_data *data);
char	**convert_envp(t_env *my_env);
//tokenize
t_line	*gen_list(char *line);
int	quoting(t_line *line);
int	piping(t_line *list, char *line);
int	redirecting(t_line *list);
void	free_line_list(t_line **list);
void	tokenize(char *line, t_data *data);
t_cmd	*sorting_by_cmd(t_line *line);
void	sorting_in_cmd(t_cmd *list);
void	create_redir_list(t_cmd *list, t_data *data);
void	convert_cmd(t_cmd *list);
void	gen_expand(t_data *data, t_cmd *cmd);
t_line*	expand_in_redir(t_data *data, t_line *redir);
void	empty_new(t_line **cursor, t_line **cmd_line, t_line *end_expand);
void	existing_new(t_line **cursor, t_line **cmd_line, t_line *end_expand, t_line *new);
void	change_hdoc(t_cmd *cmd, t_data *data);
//tokenize_utils
void	add_last_line(t_line **list, t_line *to_add);
void	add_last_in_redir(t_line **list, t_line *new);
int	is_white_space(char c);
int	is_redir_ender(char c);
int	count_inside_quote(t_line **line);
t_line	*go_to_last_node(t_line *line);
int	seek_expand_end_cmd(t_line *line);
void	dubious_redir(t_data *data);
void	find_end_expand(t_line **line);
char	*gen_name(void);
t_env	*find_env_node(t_env *env, t_line *line);
t_line	*add_quote_content(t_line *line, char *to_ret, int *i);
t_line	*create_cmd_expand(t_env *env, t_line *line);
void	dubious_redir(t_data *data);
void	check_hdoc(t_token *node, t_line *list);
void	write_in_hdoc(t_line *list, int fd);
//tokenize_clean
void	free_line_list(t_line **line);
//utils
void	ft_prompt(char **display, t_data *data);
void	ft_free_tab(char **tab);
void	ft_print_tab(char **tab);
void	free_complex_tab(char **s, int i);
void	print_complex_tab(char **s, int i);
void	ft_add_last(t_token **list, t_token *to_add);
void	ft_go_last(t_token **list);
int		tab_len(char **_stab);
int		check_first_char(char *s);
int		is_space(char c);
t_env	*go_to_env_node(t_env *list, char *s);
t_env	*env_lstnew(char *name, char *content, int status);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
char	*sanitize(char *s);
char	*join_with_space(char *s1, char *s2);
char	**split_w_space(char *s);
char	*space_strchr(char *s);
void	closer(int count, ...);
void	waiter(t_data *data, t_cmd *cmd);
void	secured_dup2(t_data *data, int fd1, int fd2);
void	secured_pipe(t_data *data, t_cmd *cmd);
pid_t	secured_fork(t_data *data);
//tokenize
char	*gen_name(void);
void	modulate_line(t_data *data, char **line, t_env *my_env);
void	is_builtin(t_cmd *list);
void	print_eof(int nb, char *limiter);
//end
void	free_token_list(t_token *to_free);
void	free_env_list(t_env *env);
void	free_cmd_list(t_cmd *to_free);
void	ft_end(t_data *data);
void	check_alloc(void *alloc, t_data *data);
//error management
void	redir_error(t_data *data, t_cmd *cmd, t_token *redirlst);
void	isdir_error(t_data *data, t_cmd *cmd);
void	fct_error(t_data *data, t_cmd *cmd);
void	export_error(t_data *data, char *arg);
//signals
void	signals_init(int type);
void	sig_handler(int sig);
//exec
void	start_exec(t_data *data);
char	**set_path(t_data *data);
void	abs_path(t_cmd *cmd);
int		check_nature(t_data *data, t_cmd *cmd, char *cmd_path);
void	call_or_exec(t_data *data, t_cmd *cmd);
//builtins
int		mns_export(t_data *data, t_cmd *cmd);
void	exp_printenv(t_env *env, t_env *tmp, char *printed, int len);
int		exp_isvalid(t_data *data, char *arg);
char	*get_pwd(t_data *data);
int		exec_cd(char **tab, t_data *data);
int		exec_pwd(t_data *data);
int		exec_unset(char **exe, t_data *data);
int		mns_env(t_data *data, t_cmd *cmd);
int		mns_exit(t_data *data, t_cmd *cmd);
int		mns_echo(t_cmd *cmd);
int		mns_mns(t_data *data, t_cmd *cmd);

#endif
