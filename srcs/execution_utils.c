# include "../minishell.h"

int	starting_exec(t_command *cmd_list, int *status, t_env_list **env)
{
	t_command	*tmp;
	t_command	*cmd;

	cmd = cmd_list;
	if (cmd->next == NULL && cmd->pipe == 0)
		{
			handle_no_pipe_cmd(cmd, status, env);
			return (0);
		}
	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->heredoc == 1)
			open_heredocs(tmp);
		tmp = tmp->next;
	}
	return (1);
}

void	waiting(int *status)
{	
	int	wstatus;

	while (wait(&wstatus) != -1 || errno != ECHILD)
	{
		if (WIFEXITED(wstatus))
			*status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			*status = 128 + WTERMSIG(wstatus);
	}
}