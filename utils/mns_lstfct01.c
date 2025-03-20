#include "../minishell.h"

t_env	*env_lstnew(char *name, char *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->content = content;
	new_node->status = 0;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

t_env	*env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = env_lstlast(*lst);
	tmp->next = new;
}