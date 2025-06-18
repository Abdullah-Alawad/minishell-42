/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:21:01 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:21:02 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_found_command(t_command *cmd, int *status, t_env_list **env)
{
	char	*path;

	if (cmd->is_builtin)
		return (1);
	else
	{
		if (!cmd->av[0])
			return (1);
		path = get_cmd_path(cmd->av[0], env);
		if (!path)
		{
			ft_putstr_fd("-minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->av[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			*status = 127;
			return (127);
		}
		free(path);
		return (1);
	}
}

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
		{
			if (open_heredocs(tmp, *env, status))
				error_exit(1, NULL, &cmd_list, env);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	waiting(int *status)
{
	int	wstatus;

	signal(SIGINT, SIG_IGN);
	while (wait(&wstatus) != -1 || errno != ECHILD)
	{
		if (WIFEXITED(wstatus))
			*status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			*status = 128 + WTERMSIG(wstatus);
	}
}

void	handle_child_cmd(t_command *cmd, int *status, t_env_list **env)
{
	if (cmd->is_builtin)
		*status = execute_builtin(cmd, *status, env);
	else
		*status = execute_external(cmd, env);
	exit (*status);
}

void	handle_no_pipe_cmd(t_command *cmd_list, int *status, t_env_list **env)
{
	t_command	*cmd;
	int			pid;

	cmd = cmd_list;
	if (check_found_command(cmd, status, env) != 127)
	{
		if (cmd->heredoc == 1)
		{
			if (open_heredocs(cmd, *env, status))
				error_exit(1, NULL, &cmd_list, env);
		}
		if (cmd->is_builtin)
			*status = execute_builtin(cmd, *status, env);
		else
		{
			pid = fork();
			if (pid == -1)
				error_exit(1, NULL, &cmd_list, env);
			if (pid == 0)
				execute_external(cmd, env);
			waiting(status);
		}
	}
}
