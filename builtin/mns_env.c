#include "../minishell.h"

void	mns_env(t_data *data)
{
	t_env	*envlst;

	envlst = data->my_env;
	while (envlst)
	{
		if (envlst->status)
			printf("%s=%s\n", envlst->name, envlst->content);
		envlst = envlst->next;
	}
}
