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

t_env_list	*init_env(char *str, int status)
{
	t_env_list	*env;
	char		**lst;

	env = malloc(sizeof(t_env_list));
	if (!env)
		return (NULL);
	lst = ft_split(str, '=');
	if (!lst)
	{
		free(env);
		return (NULL);
	}
	env->exported = status;
	if (lst[0])
		env->key = ft_strdup(lst[0]);
	else
		env->key = ft_strdup("");
	if (lst[1])
		env->data = ft_strdup(lst[1]);
	else
		env->data = ft_strdup("");
	env->len = ft_strlen(env->data);
	env->next = NULL;
	free_av(lst);
	return (env);
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
			return (0);
		env_add_back(&env_lst, tmp);
		i++;
	}
	return (env_lst);
}
