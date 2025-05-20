#include "../minishell.h"

void	remove_env(char *cmd, t_env_list **env)
{
	t_env_list	*target;
	t_env_list	*prev_tar;

	prev_tar = *env;
	if (ft_strncmp(cmd, prev_tar->key, ft_strlen(cmd)) == 0)
	{
		free(prev_tar->key);
		free(prev_tar->data);
		*env = prev_tar->next;
		free(prev_tar);
		return ;
	}
	while (prev_tar->next)
	{
		if (ft_strncmp(cmd, prev_tar->next->key, ft_strlen(cmd)) == 0)
		{
			target = prev_tar->next;
			prev_tar->next = target->next;
			free(target->data);
			free(target->key);
			free(target);
			return ;
		}
		prev_tar = prev_tar->next;
	}
}

int	in_env(char *cmd, t_env_list **env)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(cmd, tmp->key, ft_strlen(cmd)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_unset(t_command *cmd, t_env_list **env)
{
	int	i;

	i = 1;
	while (cmd->av[i])
	{
		if (in_env(cmd->av[i], env))
			remove_env(cmd->av[i], env);
		i++;
	}
	return (0);
}