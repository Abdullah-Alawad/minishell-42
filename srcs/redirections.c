#include "../minishell.h"

int	open_heredocs(t_command *cmd)
{
	int		pipes[2];
	char	*line;
	int		i;

	i = 0;
	while (cmd->here_arr && cmd->here_arr[i])
	{
		if (pipe(pipes) == -1)
			return (perror("pipe"), 1);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strncmp(line, cmd->here_arr[i],
				ft_strlen(cmd->here_arr[i])) == 0)
				break;
			write(pipes[1], line, ft_strlen(line));
			write(pipes[1], "\n", 1);
			free(line);
		}
		free(line);
		close(pipes[1]);
		if (cmd->here_arr[i + 1] == NULL)
			cmd->in_fd = pipes[0];
		else
			close(pipes[0]);
		i++;
	}
	return (0);
}

int	handle_heredoc_redirect(t_command *cmd)
{
	if (cmd->heredoc == 1 && cmd->in_fd != -1)
	{
		if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
			return (perror("dup2 heredoc"), 1);
		close(cmd->in_fd);
		cmd->in_fd = -1;
	}
	return (0);
}

int	handle_input_redirect(t_command *cmd)
{
	int	fd;

	if (cmd->heredoc == 0 && cmd->in_file)
	{
		fd = open(cmd->in_file, O_RDONLY);
		if (fd < 0)
			return (perror(cmd->in_file), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2 in_file"), 1);
		close(fd);
	}
	return (0);
}

int	handle_output_redirect(t_command *cmd)
{
	int	fd;

	if (cmd->append == 1 && cmd->out_file)
		fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->append == 2 && cmd->out_file)
		fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (0);
	if (fd < 0)
		return (perror(cmd->out_file), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2 out_file"), 1);
	close(fd);
	return (0);
}

int	redirect_fds(t_command *cmd)
{
	if (handle_heredoc_redirect(cmd))
		return (1);
	if (handle_input_redirect(cmd))
		return (1);
	if (handle_output_redirect(cmd))
		return (1);
	return (0);
}

void	reset_stds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
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