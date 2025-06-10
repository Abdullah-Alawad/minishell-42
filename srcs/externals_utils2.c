#include "../minishell.h"

int	handle_child_process(t_command *cmd, t_env_list **env, char *path)
{
	char	**envp;

	if (!redirect_fds(cmd))
		exit (1);
	envp = env_list_to_array(env);
	if (!envp)
		exit (1);
	execve(path, cmd->av, envp);
	free_av(envp);
	perror("execve");
	exit (1);
}

int	handle_parent_process(int pid, char *path)
{
	int	status;

	waitpid(pid, &status, 0);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
