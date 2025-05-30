#include "../minishell.h"

int	check_found_command(t_command *cmd, int *status, t_env_list **env)
{
	char	*path;

	if (cmd->is_builtin)
		return (1);
	else
	{
		path = get_cmd_path(cmd->av[0], env);
		if (!path)
		{
			printf("%s: command not found\n", cmd->av[0]);
			*status = 127;
			return (127);
		}
		free(path);
		return (1);
	}
}

int	execute_builtin(t_command *cmd, int status, t_env_list **env)
{
	if (!cmd || !cmd->av)
		return (1);
	if (ft_strncmp("echo", cmd->av[0], ft_strlen("echo")) == 0)
		status = handle_echo(cmd->av);
	else if (ft_strncmp("env", cmd->av[0], ft_strlen("env")) == 0)
		status = handle_env(env);
	else if (ft_strncmp("pwd", cmd->av[0], ft_strlen("pwd")) == 0)
		status = handle_pwd();
	else if (ft_strncmp("cd", cmd->av[0], ft_strlen("cd")) == 0)
		status = handle_cd(cmd->av, env);
	else if (ft_strncmp("exit", cmd->av[0], ft_strlen("exit")) == 0)
		status = handle_exit(env, &cmd, status);
	else if (ft_strncmp("export", cmd->av[0], ft_strlen("export")) == 0)
		status = handle_export(cmd, env);
	else if (ft_strncmp("unset", cmd->av[0], ft_strlen("unset")) == 0)
		status = handle_unset(cmd, env);
	return (status);
}

void	handle_no_pipe_cmd(t_command *cmd_list, int *status, t_env_list **env)
{
	t_command	*cmd;
	int			stdin_c;
	int			stdout_c;

	cmd = cmd_list;
	if (check_found_command(cmd, status, env) != 127)
	{	
		if (cmd->heredoc == 1)
			open_heredocs(cmd);
		if (need_redirect(cmd))
		{	
			stdin_c = dup(STDIN_FILENO);
			stdout_c = dup(STDOUT_FILENO);
		}
		if (!redirect_fds(cmd))
		{
			if (cmd-> is_builtin)
				*status = execute_builtin(cmd, *status, env);
			else
				*status = execute_external(cmd, env);
		}
		if (need_redirect(cmd))
			reset_stds(stdin_c, stdout_c);
	}
}

void	execute_command(t_command *cmd_list, int *status, t_env_list **env)
{
	t_command	*cmd;
	int			pipes[2];
	pid_t		pid;		
	int			stdin_c;
	int			stdout_c;
	int			prev_fd;
	int			wstatus;

	cmd = cmd_list;
	prev_fd = -1;
	if (cmd->next == NULL && cmd->pipe == 0)
	{
		handle_no_pipe_cmd(cmd, status, env);
		return ;
	}
	t_command *tmp = cmd_list;
	while (tmp)
	{
		if (tmp->heredoc == 1)
			open_heredocs(tmp);
		tmp = tmp->next;
	}
	while (cmd)
	{
		if (cmd->next && pipe(pipes) == -1)
			error_exit(1, NULL, &cmd_list, env);
		pid = fork();
		if (pid == 0)
		{
			/*new*/
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);

			if (cmd->next)
				dup2(pipes[1], STDOUT_FILENO);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipes[0]);
				close(pipes[1]);
			}
			/*till here*/
			if (check_found_command(cmd, status, env) != 127)
			{	
				// if (cmd->heredoc == 1)
				// 	open_heredocs(cmd);
				if (need_redirect(cmd))
				{	
					stdin_c = dup(STDIN_FILENO);
					stdout_c = dup(STDOUT_FILENO);
				}
				if (!redirect_fds(cmd))
				{
					if (cmd-> is_builtin)
						*status = execute_builtin(cmd, *status, env);
					else
						*status = execute_external(cmd, env);
				}
				if (need_redirect(cmd))
					reset_stds(stdin_c, stdout_c);
				exit (*status);
			}
			else
				exit (*status);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
				close(pipes[1]);
			if (cmd->in_fd > 2)
				close(cmd->in_fd);
			prev_fd = (cmd->next) ? pipes[0] : -1;
		}
		cmd = cmd->next;
	}
	while (wait(&wstatus) != -1 || errno != ECHILD)
	{
		if (WIFEXITED(wstatus))
			*status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			*status = 128 + WTERMSIG(wstatus);
	}

}
