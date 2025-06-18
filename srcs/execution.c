/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:20:38 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/18 14:25:27 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_builtin(t_command *cmd, int status, t_env_list **env)
{
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

int	execute_builtin(t_command *cmd, int status, t_env_list **env)
{
	int	std[2];

	if (!cmd || !cmd->av)
		return (1);
	if (need_redirect(cmd))
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
	}
	if (redirect_fds(cmd))
		status = run_builtin(cmd, status, env);
	else
	{
		if (need_redirect(cmd))
			reset_stds(std);
		return (1);
	}
	if (need_redirect(cmd))
		reset_stds(std);
	return (status);
}

void	handle_child(t_command *cmd, int *status,
		t_pipe *pipe, t_env_list **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipe->prev_fd != -1)
		dup2(pipe->prev_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pipe->pipes[1], STDOUT_FILENO);
	if (pipe->prev_fd != -1)
		close(pipe->prev_fd);
	if (cmd->next)
	{
		close(pipe->pipes[0]);
		close(pipe->pipes[1]);
	}
	if (check_found_command(cmd, status, env) != 127)
		handle_child_cmd(cmd, status, env);
	else
		exit (*status);
}

void	in_parent(t_command *cmd, t_pipe *pipe)
{
	if (pipe->prev_fd != -1)
		close(pipe->prev_fd);
	if (cmd->next)
		close(pipe->pipes[1]);
	if (cmd->in_fd != -1)
	{
		close(cmd->in_fd);
		cmd->in_fd = -1;
	}
	if (cmd->next)
		pipe->prev_fd = pipe->pipes[0];
	else
		pipe->prev_fd = -1;
}

int	execute_command(t_command *cmd_list, int *status, t_env_list **env)
{
	t_command	*cmd;
	t_pipe		pipe_s;

	cmd = cmd_list;
	pipe_s.prev_fd = -1;
	if (!starting_exec(cmd_list, status, env))
		return (*status);
	t_command *cmds = cmd_list;
	int i = 0;
	while (cmds)
	{
		printf("in fd[%d]: %d\n", i, cmds->in_fd);
		cmds = cmds->next;
		i++;
	}
	while (cmd)
	{
		if (cmd->next && pipe(pipe_s.pipes) == -1)
			error_exit(1, NULL, &cmd_list, env);
		pipe_s.pid = fork();
		if (pipe_s.pid == -1)
			error_exit(1, NULL, &cmd_list, env);
		if (pipe_s.pid == 0)
			handle_child(cmd, status, &pipe_s, env);
		else
			in_parent(cmd, &pipe_s);
		cmd = cmd->next;
	}
	waiting(status);
	return (*status);
}
