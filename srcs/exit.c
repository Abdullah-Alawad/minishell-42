#include "../minishell.h"

int	handle_exit(t_env_list **env, t_command **cmd, int status)
{
	free_commands(cmd);
	free_env_list(env);
	printf("status in exit: %d\n", status);
	rl_clear_history();
	exit(status); // status of last exected command
}
