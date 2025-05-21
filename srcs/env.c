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
	char		*equal_sign;
	size_t		key_len;

	env = malloc(sizeof(t_env_list));
	if (!env)
		return (NULL);

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		env->key = ft_strdup(str);
		env->data = ft_strdup("");
	}
	else
	{
		key_len = equal_sign - str;
		env->key = ft_substr(str, 0, key_len);
		env->data = ft_strdup(equal_sign + 1);
	}
	env->exported = status;
	env->len = ft_strlen(env->data);
	env->next = NULL;
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
