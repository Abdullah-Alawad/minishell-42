#include "../minishell.h"

void	find_pwd_and_oldpwd(t_env_list *head, t_env_list **pwd,
		t_env_list **old_pwd)
{
	while (head)
	{
		if (ft_strncmp("PWD", head->key, ft_strlen(head->key)) == 0)
			*pwd = head;
		if (ft_strncmp("OLDPWD", head->key, ft_strlen(head->key)) == 0)
			*old_pwd = head;
		head = head->next;
	}
}

void	update_pwd(t_env_list **env)
{
	t_env_list	*pwd;
	t_env_list	*old_pwd;

	pwd = NULL;
	old_pwd = NULL;
	find_pwd_and_oldpwd(*env, &pwd, &old_pwd);
	handle_oldpwd(env, &old_pwd);
	update_pwd_data(pwd, old_pwd);
}

int	handle_cd_path(char **cmd, t_env_list **env, int num, int is_tilde)
{
	char	*tmp;

	if (num == 2)
	{
		tmp = cmd[1];
		if (is_tilde && tmp[1] == '/')
			tmp += 2;
		if (chdir(tmp) != 0)
		{
			perror("cd");
			return (1);
		}
		update_pwd(env);
	}
	return (0);
}

int	handle_cd_home(char **cmd, t_env_list **env, int num, int is_tilde)
{
	char	*path;

	path = get_home_path(env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (1);
	if ((is_tilde && cmd[1][1] == '\0') || num == 1)
	{
		update_pwd(env);
		return (0);
	}
	return (-1);
}

int	handle_cd(char **cmd, t_env_list **env)
{
	int		num;
	int		is_tilde;
	int		status;

	is_tilde = 0;
	status = 0;
	num = count_av(cmd);
	if (num > 2)
	{
		perror("cd: too many arguments\n");
		return (1);
	}
	if (num == 2 && cmd[1][0] == '~')
		is_tilde = 1;
	if (num == 1 || (num == 2 && is_tilde))
	{
		status = handle_cd_home(cmd, env, num, is_tilde);
		if (status != -1)
			return (status);
	}
	status = handle_cd_path(cmd, env, num, is_tilde);
	return (status);
}
