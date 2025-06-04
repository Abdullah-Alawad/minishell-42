#include "../minishell.h"

char	*handle_shlvl(char *equal_sign)
{
	char	*res;
	int		lvl;

	res = ft_strdup(equal_sign + 1);
	if (!res)
		return (NULL);
	lvl = ft_atoi(res);
	lvl++;
	free(res);
	res = ft_itoa(lvl);
	if (!res)
		return (NULL);
	return (res);
}

int	split_env(t_env_list *env, char *str, char *equal_sign, size_t key_len)
{
	key_len = equal_sign - str;
	env->key = ft_substr(str, 0, key_len);
	if (!env->key)
	{
		free_env_list(&env);
		return (0);
	}
	if (ft_strncmp(env->key, "SHLVL", ft_strlen("SHLVL")) == 0)
		env->data = handle_shlvl(equal_sign);
	else
		env->data = ft_strdup(equal_sign + 1);
	if (!env->data)
	{
		free_env_list(&env);
		return (0);
	}
	return (1);
}

int	add_no_equal(t_env_list *env, char *str)
{
	env->key = ft_strdup(str);
	env->data = ft_strdup("");
	if (!env->key || !env->data)
	{
		free_env_list(&env);
		return (0);
	}
	return (1);
}

t_env_list	*init_env(char *str, int status)
{
	t_env_list	*env;
	char		*equal_sign;
	size_t		key_len;

	key_len = 0;
	env = malloc(sizeof(t_env_list));
	if (!env)
		return (NULL);
	env->next = NULL;
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		if (!add_no_equal(env, str))
			return (NULL);
	}
	else
	{
		if (!split_env(env, str, equal_sign, key_len))
			return (NULL);
	}
	env->exported = status;
	env->len = ft_strlen(env->data);
	return (env);
}
