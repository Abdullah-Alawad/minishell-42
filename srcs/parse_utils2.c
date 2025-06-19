/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:19:37 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/19 15:19:38 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_cmd(t_command *cmd)
{
	cmd->here_arr[0] = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	cmd->pipe = 0;
	cmd->heredoc = 0;
	cmd->append = 0;
	cmd->is_builtin = 0;
	cmd->redirect_in_type = -1;
}

t_command	*cmd_create(int status)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->av = malloc(sizeof(char *) * 1);
	if (!cmd->av)
	{
		free(cmd);
		return (NULL);
	}
	cmd->av[0] = NULL;
	cmd->here_arr = malloc(sizeof(char *) * 1);
	if (!cmd->here_arr)
	{
		free_commands(&cmd);
		return (NULL);
	}
	fill_cmd(cmd);
	cmd->status = status;
	return (cmd);
}
