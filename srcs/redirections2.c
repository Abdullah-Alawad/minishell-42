/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:25:08 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:25:10 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_line(char *line, t_env_list *env, int status)
{
	char	*result;

	result = heredoc_expander(line, env, status, NULL);
	if (!result)
		return (NULL);
	return (result);
}

void	write_heredoc(char *line, int fd, t_env_list *env, int *status)
{
	line = expand_line(line, env, *status);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

int	open_heredocs(t_command *cmd, t_env_list *env, int *status)
{
	t_heredoc	heredoc;

	heredoc.i = 0;
	while (cmd->here_arr && cmd->here_arr[heredoc.i])
	{
		if (pipe(heredoc.pipes) == -1)
			return (1);
		while (1)
		{
			heredoc.line = readline("> ");
			if (!heredoc.line)
				return (1);
			if (ft_strcmp(heredoc.line, cmd->here_arr[heredoc.i]) == 0)
				break ;
			write_heredoc(heredoc.line, heredoc.pipes[1], env, status);
		}
		free(heredoc.line);
		close(heredoc.pipes[1]);
		if (cmd->here_arr[heredoc.i + 1] == NULL && cmd->redirect_in_type == 2)
			cmd->in_fd = heredoc.pipes[0];
		else
			close(heredoc.pipes[0]);
		heredoc.i++;
	}
	return (0);
}

int	need_redirect(t_command *cmd)
{
	if (cmd->heredoc == 1)
		return (1);
	else if (cmd->append == 1 || cmd->append == 2)
		return (1);
	else if (cmd->in_file)
		return (1);
	else
		return (0);
}

int	write_fd_error(char *file)
{
	struct stat	fs;

	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	if (stat(file, &fs) == 0)
	{
		if (S_ISDIR(fs.st_mode))
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	}
	else
	{
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	}
	return (1);
}
