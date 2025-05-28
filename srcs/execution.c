#include "../minishell.h"

int	execute_builtin(t_command *cmd, char *command, int status, t_env_list **env)
{
	(void)command;
	if (!cmd || !cmd->av)
		return (1);
	if (ft_strncmp("echo", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
		status = handle_echo(cmd->av);
	else if (ft_strncmp("env", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
		status = handle_env(env);
	// else if (ft_strncmp("pwd", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
	// 	status = handle_pwd();
	else if (ft_strncmp("cd", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
		status = handle_cd(cmd->av, env);
	else if (ft_strncmp("exit", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
		status = handle_exit(env, &cmd, status);
	else if (ft_strncmp("export", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
		status = handle_export(cmd, env);
	else if (ft_strncmp("unset", cmd->av[0], ft_strlen(cmd->av[0])) == 0)
		status = handle_unset(cmd, env);
	return (status);
}

void	execute_command(t_command *cmd_list, char *command,
	int *status, t_env_list **env)
{
	t_command	*cmd;
	int			stdin_c;
	int			stdout_c;

	cmd = cmd_list;
	while (cmd)
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
				*status = execute_builtin(cmd, command, *status, env);
			else
				*status = execute_external(cmd, env);
		}
		if (need_redirect(cmd))
			reset_stds(stdin_c, stdout_c);
		cmd = cmd->next;
	}
}
