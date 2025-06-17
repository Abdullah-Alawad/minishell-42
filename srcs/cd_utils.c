/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:20:50 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:20:52 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_av(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_home_path(t_env_list **env)
{
	char		*path;
	t_env_list	*head;

	path = NULL;
	head = *env;
	while (head)
	{
		if (ft_strncmp("HOME", head->key, ft_strlen(head->key)) == 0)
			path = head->data;
		head = head->next;
	}
	return (path);
}

void	update_pwd_data(t_env_list *pwd, t_env_list *old_pwd)
{
	char	*cwd;

	if (old_pwd && pwd)
	{
		free(old_pwd->data);
		old_pwd->data = ft_strdup(pwd->data);
	}
	if (pwd)
	{
		free(pwd->data);
		cwd = getcwd(NULL, 0);
		if (cwd)
			pwd->data = cwd;
		else
			pwd->data = NULL;
	}
}

void	handle_oldpwd(t_env_list **env, t_env_list **old_pwd)
{
	char	*tmp;

	if (!*old_pwd)
	{
		tmp = ft_strjoin("OLDPWD=", "tmp_path");
		if (!tmp)
			return ;
		*old_pwd = init_env(tmp, 0);
		free(tmp);
		if (!*old_pwd)
			return ;
		env_add_back(env, *old_pwd);
	}
}
