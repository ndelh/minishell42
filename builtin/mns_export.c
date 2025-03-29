#include "../minishell.h"

//prints env new->contents in ascii order.
static void	ft_printenv(t_env *env, t_env *tmp, char *printed, int len)
{
	t_env	*to_print;

	to_print = tmp;
	while (len--)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, to_print->name) < 0
				&& ft_strcmp(tmp->name, printed) > 0)
				to_print = tmp;
			else if (ft_strcmp(to_print->name, printed) <= 0)
				to_print = tmp;
			tmp = tmp->next;
		}
		if (ft_strcmp(to_print->name, "_"))
		{
			printf("declare -x %s", to_print->name);
			if (to_print->content)
				printf("=\"%s\"", to_print->content);
			printf("\n");
		}
		printed = to_print->name;
		tmp = env;
	}
}

//checks if arg is valid.
static int	ft_isvalid(t_data *data, char *arg)
{
	char	*tmp;

	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(*arg) && *arg != '_')
	{
		export_error(data, arg);
		return (0);
	}
	tmp = arg;
	while (*tmp && *tmp != '=' && *tmp != '+')
	{
		if (!ft_isalnum(*tmp) && *tmp != '_')
		{
			export_error(data, arg);
			return (0);
		}
		tmp++;
	}
	return (1);
}

//checks if name already exists. 
//If yes, changes or cats new->content. else, addback.
static void	add_arg_2(t_env *envlst, char *arg, t_env *new, int len)
{
	t_env	*tmp;
	char	*old_content;

	tmp = envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new->name))
		{
			free(new->name);
			if (arg[len - 1] == '+')
			{
				old_content = tmp->content;
				tmp->content = ft_strjoin(tmp->content, new->content);
				free(old_content);
				free(new->content);
				return ;
			}
			free(tmp->content);
			tmp->content = new->content;
			return ;
		}
		tmp = tmp->next;
	}
	env_lstadd_back(&envlst, env_lstnew(new->name, new->content, new->status));
}

//adds valid arg to env. '_' new->content will not be modified.
static void	add_arg_1(t_data *data, t_env *envlst, char *arg)
{
	t_env	new;
	int		len;

	if (!ft_isvalid(data, arg) || (*arg == '_' && (*(arg + 1) == '='
				|| *(arg + 1) == '\0' || *(arg + 1) == '+')))
		return ;
	if (ft_strchr(arg, '='))
	{
		len = ft_strchr(arg, '=') - arg;
		if (arg[len - 1] == '+')
			new.name = ft_substr(arg, 0, len - 1);
		else
			new.name = ft_substr(arg, 0, len);
		new.content = ft_substr(arg, len + 1, ft_strlen(arg) - len);
		new.status = 1;
	}
	else
	{
		len = ft_strlen(arg);
		new.name = ft_strdup(arg);
		new.status = 0;
		new.content = NULL;
	}
	add_arg_2(envlst, arg, &new, len);
}

//checks args. no args: display sorted env. valid args: add to env.
//returns 0 on success, number of names it failed to add in env upon failure.
int	mns_export(t_data *data, t_cmd *cmd)
{
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	if (!cmd->cmd_arg[1])
		ft_printenv(data->my_env, data->my_env, "",
			ft_lstsize((void *)data->my_env));
	while (cmd->cmd_arg[i])
		add_arg_1(data, data->my_env, cmd->cmd_arg[i++]);
	ft_free_tab(data->envp);
	data->envp = convert_envp(data->my_env);
	return (ret);
}
