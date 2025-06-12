#include "../minishell.h"

int	handle_external_cmd(t_command *cmd, char *path, char **envp)
{
	if (!redirect_fds(cmd))
		exit (1);
	execve(path, cmd->av, envp);
	free_av(envp);
	perror("execve");
	exit (1);
}

int	external_error(char *path, char **envp)
{
	free(path);
	free_av(envp);
	return (-1);
}
