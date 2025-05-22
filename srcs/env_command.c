#include "../minishell.h"

int	handle_env(t_env_list **env)
{
	t_env_list	*head;

	head = *env;
	while (head)
	{
		if (head->exported == 0)
			printf("%s=%s\n", head->key, head->data);
		else if (head->exported == 1)
			printf("%s=\n", head->key);
		head = head->next;
	}
	return (0);
}
