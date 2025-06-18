/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:21:39 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:21:41 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc(t_command *cmd)
{
	while (cmd->next)
	{
		if (cmd->next->heredoc)
			close(cmd->next->in_fd);
		cmd = cmd->next;
	}
}

int	handle_external_cmd(t_command *cmd, char *path,
	char **envp, t_env_list **env)
{
	if (!redirect_fds(cmd))
	{
		free_av(envp);
		free(path);
		error_exit(1, NULL, &cmd, env);
	}
	close_heredoc(cmd);
	execve(path, cmd->av, envp);
	free_av(envp);
	free(path);
	perror("execve");
	if (errno == EACCES)
		error_exit(126, NULL, &cmd, env);
	else
		error_exit(1, NULL, &cmd, env);
	exit (1);
}

int	external_error(char *path, char **envp)
{
	free(path);
	free_av(envp);
	return (-1);
}
