#include "../minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*get_positional_value(char *num_str, char **args, int status)
{
	int	index;

	if (!args)
		return (NULL);
	if (ft_strcmp(num_str, "?") == 0)
		return (ft_itoa(status));
	index = ft_atoi(num_str);
	if (index == 0)
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

void	expand_braced_variable(char *data, t_expand *ex)
{
	ex->i++;
	ex->start = ex->i;
	while (data[ex->i] && data[ex->i] != '}')
		ex->i++;
	ex->var_name = ft_substr(data, ex->start, ex->i - ex->start);
	if (ft_isdigit(ex->var_name[0]))
		ex->value = get_positional_value(ex->var_name, ex->args, ex->status);
	else
		ex->value = get_env_value(ex->var_name, ex->env_lst);
	if (ex->value)
		ex->result = ft_strjoin_and_free(ex->result, ex->value);
	else
		ex->result = ft_strjoin_and_free(ex->result, "");
	free(ex->var_name);
	if (data[ex->i] == '}')
		ex->i++;
}

void	expand_status_variable(t_expand *ex)
{
	char	*status_str;

	ex->i++;
	status_str = ft_itoa(ex->status);
	ex->result = ft_strjoin_and_free(ex->result, status_str);
	free(status_str);
}

