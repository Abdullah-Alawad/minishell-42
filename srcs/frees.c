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
