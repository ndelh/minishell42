#include "../minishell.h"

//prints env new->contents in ascii order.
static void	ft_printenv(t_env *env, char *printed, int len)
{
	t_env	*tmp;
	t_env	*to_print;

	tmp = env;
	to_print = tmp;
	// len = ft_lstsize((void *)env);//needs check if the cast works in this situation
	while (len--)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, to_print->name) < 0 
				&& ft_strcmp(tmp->name, printed) > 0)
				to_print = tmp;
			tmp = tmp->next;
		}
		if (ft_strcmp(to_print->name, "_"))
		{
			printf("declare -x %s", to_print->name);
			if (to_print->content)
				printf("=\"%s\"", to_print->content);
			write(1, "\n", 1);
		}
		printed = to_print->name;
		tmp = env;
	}
}

//checks if arg is valid.
static int	ft_isvalid(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
	{
		errno = EINVAL;//not the right error
		perror(arg);//export: 'arg': not a valid identifier;
		g_status = 1;
		return (0);
	}
	while (*arg && (*arg != '=' || *arg != '+'))
	{
		if (!ft_isalnum(*arg) && *arg != '_')
		{
			errno = EINVAL;//not the right error
			perror(arg);//export: 'arg': not a valid identifier;
			return (0);
		}
		arg++;
	}
	return (1);
}

//checks if name already exists. If yes, changes or cats new->content. else, addback.
static void	add_arg_2(t_env *envlst,char *arg, t_env *new, int len)
{
	while (envlst)
	{
		if (new->name == envlst->name)
		{
			free(new->name);
			if (arg[len - 2] == '+')
			{
				ft_strlcat(envlst->content, new->content, 
				ft_strlen(envlst->content) + ft_strlen(new->content));// + 1?
				return ;
			}
			free(envlst->content);
			envlst->content = new->content;
			return ;
		}
		envlst = envlst->next;
	}
	envlst->next = env_lstnew(new->name, new->content);
}

//adds valid arg to env. '_' new->content will not be modified.
static void	add_arg_1(t_env *envlst, char *arg)
{
	t_env	new;
	int		len;

	if (!ft_isvalid(arg) || 
	(*arg == '_' &&  (*(arg + 1) == '=' || *(arg + 1) == '\0')))
		return ;
	len = arg - ft_strchr(arg, '=');
	if (arg[len - 2] == '+')
		new.name = ft_substr(arg, 0, len - 2);
	else
		new.name = ft_substr(arg, 0, len - 1);
	new.content = ft_substr(arg, len, ft_strlen(arg) - len);
	add_arg_2(envlst, arg, &new, len);
}

//checks args. no args: display sorted env. valid args: add to env.
//returns 0 on success, number of names it failed to add in env upon failure.
int	mns_export(t_data *data, t_cmd *cmd)
{
	int			ret;//==number of names export failed to add in env.

	ret = 0;
	if (!cmd->cmd_arg[1])
		ft_printenv(data->my_env, "", ft_lstsize((void *)data->my_env));
	while (++cmd->cmd_arg)
	{
		add_arg_1(data->my_env, *(cmd->cmd_arg));
	}
	return (ret);
}
