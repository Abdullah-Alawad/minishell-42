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

int	new_export(char *cmd, t_env_list **env)
{
	int			len;
	t_env_list	*tmp;

	tmp = *env;
	len = ft_strchr_i(cmd, '=');
	if (len == 0)
		len = ft_strlen(cmd) + 1;
	while (tmp)
	{
		if (ft_strncmp(cmd, tmp->key, len - 1) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	update_env(char *cmd, t_env_list **env)
{
	int			start;
	int			len;
	char		*new_data;
	t_env_list	*tmp;

	tmp = *env;
	len = ft_strlen(cmd);
	start = ft_strchr_i(cmd, '=');
	new_data = ft_substr(cmd, start + 1, len - (start + 1));
	if (!new_data)
		return ; //double check
	while (tmp)
	{
		if (ft_strncmp(cmd, tmp->key, start - 1) == 0)
		{
			free(tmp->data);
			tmp->data = new_data;
			return ;
		}
		tmp = tmp->next;
	}
}

int	add_export(char **cmd, t_env_list **env)
{
	int			i;
	t_env_list	*new;
	int			exp;

	i = 1;
	while (cmd[i])
	{
		exp = check_export_format(cmd[i]);
		if (new_export(cmd[i], env))
		{
			if (exp == 2)
				new = init_special_env(cmd[i], exp);
			else
				new = init_env(cmd[i], exp);
			if (!new)
				return (1); // double check
			env_add_back(env, new);
		}
		else
			update_env(cmd[i], env);
		i++;
	}
	return (0);
}

int	handle_export(t_command *cmd, t_env_list **env)
{
	if (!cmd->av[1])
	{
		print_export(env);
		return (0);
	}
	else
	{
		// you can check export format ****
		if (!add_export(cmd->av, env))
			return (0);
		else
		{
			error_exit(1, NULL, &cmd, env);
			return (1);
		}
	}
}
