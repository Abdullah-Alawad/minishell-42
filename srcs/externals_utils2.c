#include "../minishell.h"

int	handle_external_cmd(t_command *cmd, char *path,
	char **envp, t_env_list **env)
{
	if (!redirect_fds(cmd))
	{
		free_av(envp);
		free(path);
		error_exit(1, NULL, &cmd, env);
	}
	execve(path, cmd->av, envp);
	free_av(envp);
	free(path);
	perror("execve");
	error_exit(1, NULL, &cmd, env);
	exit (1);
}

int	external_error(char *path, char **envp)
{
	free(path);
	free_av(envp);
	return (-1);
}
