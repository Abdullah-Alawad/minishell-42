/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:25:02 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:25:04 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc_redirect(t_command *cmd)
{
	if (cmd->heredoc == 1 && cmd->in_fd != -1)
	{
		if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
			return (1);
		close(cmd->in_fd);
		cmd->in_fd = -1;
	}
	return (0);
}

int	handle_input_redirect(t_command *cmd)
{
	int			fd;
	char		*file;
	struct stat	fs;

	file = cmd->in_file;
	if (cmd->heredoc == 0 && cmd->in_file)
	{
		fd = open(cmd->in_file, O_RDONLY);
		if (fd < 0)
			return (write_fd_error(file));
		if (stat(file, &fs) == 0 && S_ISDIR(fs.st_mode))
		{
			close(fd);
			return (write_fd_error(file));
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
		cmd->in_fd = -1;
	}
	return (0);
}

int	handle_output_redirect(t_command *cmd)
{
	int		fd;
	char	*file;

	file = cmd->out_file;
	if (cmd->append == 1 && cmd->out_file)
		fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->append == 2 && cmd->out_file)
		fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (0);
	if (fd < 0)
		return (write_fd_error(file));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	close(fd);
	cmd->out_fd = -1;
	return (0);
}

int	redirect_fds(t_command *cmd)
{
	if (handle_heredoc_redirect(cmd))
		return (0);
	if (handle_input_redirect(cmd))
		return (0);
	if (handle_output_redirect(cmd))
		return (0);
	return (1);
}

void	reset_stds(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}
