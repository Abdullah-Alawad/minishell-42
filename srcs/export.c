/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:22:20 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:22:21 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_data(char *cmd, char *new_data, size_t start,
		t_env_list *tmp)
{
	while (tmp)
	{
		if (ft_strncmp(cmd, tmp->key, start) == 0
			&& ft_strlen(tmp->key) == start)
		{
			free(tmp->data);
			tmp->data = new_data;
			if (tmp->data[0] != '\0')
				tmp->exported = 0;
			else
				tmp->exported = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

int	update_env(char *cmd, t_env_list **env)
{
	size_t		start;
	int			len;
	char		*new_data;
	t_env_list	*tmp;

	tmp = *env;
	len = ft_strlen(cmd);
	start = ft_strchr_i(cmd, '=');
	if (start == 0)
		return (1);
	new_data = ft_substr(cmd, start + 1, len - (start + 1));
	if (!new_data)
		return (0);
	update_env_data(cmd, new_data, start, tmp);
	return (1);
}

int	add_new_export(char *cmd, t_env_list **env, int exp)
{
	t_env_list	*new;

	if (exp == 2)
		new = init_special_env(cmd, exp);
	else
		new = init_env(cmd, exp);
	if (!new)
		return (0);
	env_add_back(env, new);
	return (1);
}

int	add_export(char **cmd, t_env_list **env)
{
	int			i;
	int			exp;

	i = 1;
	while (cmd[i])
	{
		if (valid_export(cmd[i]))
		{
			exp = check_export_format(cmd[i]);
			if (new_export(cmd[i], env, exp))
			{
				if (!add_new_export(cmd[i], env, exp))
					return (1);
			}
			else
			{
				if (!update_env(cmd[i], env))
					return (1);
			}
		}
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
		if (!add_export(cmd->av, env))
			return (0);
		else
			return (-1);
	}
}
