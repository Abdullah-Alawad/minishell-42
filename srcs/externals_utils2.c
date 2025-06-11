#include "../minishell.h"

int	handle_child_process(t_command *cmd, char *path, char **envp)
{
	if (!redirect_fds(cmd))
		exit (1);
	execve(path, cmd->av, envp);
	free_av(envp);
	perror("execve");
	exit (1);
}

int	handle_parent_process(int pid, char *path, char **envp)
{
	int	status;

	waitpid(pid, &status, 0);
	free_av(envp);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	external_error(char *path, char **envp)
{
	free(path);
	free_av(envp);
	return (-1);
}
