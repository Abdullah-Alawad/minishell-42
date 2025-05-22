#include "../minishell.h"

void	free_tokens(t_token **tokens_list)
{
	t_token	*tmp;

	if (!tokens_list)
		return ;
	while (*tokens_list)
	{
		tmp = (*tokens_list)->next;
		free((*tokens_list)->data);
		free(*tokens_list);
		*tokens_list = tmp;
	}
}

void	free_av(char **s)
{
	int		len;

	if (!s || !*s)
		return ;
	len = 0;
	while (s[len])
	{
		free(s[len]);
		len++;
	}
	free(s);
}

void	free_env_list(t_env_list **env)
{
	t_env_list	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->data)
			free((*env)->data);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

void	free_commands(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds)
		return ;
	while (*cmds)
	{
		tmp = ((*cmds)->next);
		if ((*cmds)->in_file)
			free((*cmds)->in_file);
		if ((*cmds)->out_file)
			free((*cmds)->out_file);
		if ((*cmds)->av)
			free_av((*cmds)->av);
		free(*cmds);
		*cmds = tmp;
	}
}

void	error_exit(int status, t_token **tokens,
	t_command **cmds, t_env_list **env)
{
	free_tokens(tokens);
	free_env_list(env);
	free_commands(cmds);
	exit(status);
}
