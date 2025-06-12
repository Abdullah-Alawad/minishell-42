#include "../minishell.h"

t_env_list	*env_last(t_env_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_add_back(t_env_list **lst, t_env_list *env)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = env;
	else
		(env_last(*lst))->next = env;
}

t_env_list	*create_env_list(char **env)
{
	int			i;
	t_env_list	*env_lst;
	t_env_list	*tmp;

	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		tmp = init_env(env[i], 0);
		if (!tmp)
		{
			free_env_list(&env_lst);
			return (0);
		}
		env_add_back(&env_lst, tmp);
		i++;
	}
	return (env_lst);
}
