#include "../minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*get_positional_value(char *num_str, char **args)
{
	int	index;

	index = ft_atoi(num_str);
	if (!args)
		return (NULL);
	if (args[index])
		return (args[index]);
	return ("");
}

char	*get_env_value(char *var_name, t_env_list *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->data);
		env = env->next;
	}
	return (NULL);
}
