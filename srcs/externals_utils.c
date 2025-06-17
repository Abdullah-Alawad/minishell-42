/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:21:30 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:21:32 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_envs(t_env_list *env, char **envp, char *tmp)
{
	int		i;

	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (1);
		if (!env->data)
			envp[i] = tmp;
		else
		{
			envp[i] = ft_strjoin(tmp, env->data);
			if (!envp[i])
			{
				free(tmp);
				return (1);
			}
			free(tmp);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (0);
}

int	env_len(t_env_list *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**env_list_to_array(t_env_list **env)
{
	int		envp_len;
	char	**envp;
	char	*tmp;

	tmp = NULL;
	envp_len = env_len(*env);
	envp = malloc(sizeof(char *) * (envp_len + 1));
	if (!envp)
		return (NULL);
	if (add_envs(*env, envp, tmp))
		return (NULL);
	return (envp);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_env_path(t_env_list *env)
{
	t_env_list	*tmp;
	int			len;

	tmp = env;
	while (tmp)
	{
		if (tmp->key)
		{
			len = ft_strlen(tmp->key);
			if (ft_strncmp(tmp->key, "PATH", len) == 0)
				return (tmp->data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
