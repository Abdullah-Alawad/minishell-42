#include "../minishell.h"

void	exit_expand_error(char *cmd, t_env_list **env, t_expand **ex)
{
	free(cmd);
	free_env_list(env);
	rl_clear_history();
	if (ex)
	{
		if (*ex)
		{
			if ((*ex)->result)
				free((*ex)->result);
			free(*ex);
		}
	}
	exit(1);
}
