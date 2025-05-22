#include "../minishell.h"

t_env_list	*init_special_env(char *str, int status)
{
	t_env_list	*env;

	env = malloc(sizeof(t_env_list));
	if (!env)
		return (NULL);
	env->exported = status;
	env->len = 0;
	env->key = ft_strdup(str);
	if (!env->key)
	{
		free(env);
		return (NULL);
	}
	env->data = ft_strdup("");
	if (!env->data)
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

void	print_export(t_env_list **env)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->exported == 2)
			printf("declare -x %s\n", tmp->key);
		else if (tmp->exported == 1)
			printf("declare -x %s=\"\"\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->data);
		tmp = tmp->next;
	}
}

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (0);
}
