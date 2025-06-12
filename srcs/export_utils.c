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

int	print_export_error(char *cmd)
{
	ft_putstr_fd("-minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (0);
}

int	valid_export(char *cmd)
{
	int	i;

	if (!cmd[0])
		return (0);
	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (print_export_error(cmd));
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (print_export_error(cmd));
		i++;
	}
	return (1);
}
