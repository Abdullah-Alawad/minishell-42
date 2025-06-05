#include "../minishell.h"

int	check_export_format(char *cmd)
{
	int	pos;

	if (ft_strchr_i(cmd, '='))
	{
		pos = ft_strchr_i(cmd, '=');
		if (cmd[pos - 1] && cmd[pos + 1])
			return (0);
		else if (cmd[pos - 1])
			return (1);
	}
	return (2);
}

int	new_export(char *cmd, t_env_list **env, int exp)
{
	size_t		len;
	t_env_list	*tmp;

	tmp = *env;
	len = ft_strchr_i(cmd, '=');
	if (len == 0)
		len = ft_strlen(cmd);
	while (tmp)
	{
		if ((exp == 2 && ft_strcmp(cmd, tmp->key) == 0) ||
    	(exp != 2 && ft_strncmp(cmd, tmp->key, len) == 0 && ft_strlen(tmp->key) == len))
		return (0);
		tmp = tmp->next;
	}
	return (1);
}
