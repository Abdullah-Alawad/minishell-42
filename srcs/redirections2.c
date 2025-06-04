#include "../minishell.h"

void	write_heredoc(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

int	open_heredocs(t_command *cmd)
{
	int		pipes[2];
	char	*line;
	int		i;

	i = 0;
	while (cmd->here_arr && cmd->here_arr[i])
	{
		if (pipe(pipes) == -1)
			return (1);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, cmd->here_arr[i]) == 0)
				break;
			write_heredoc(line, pipes[1]);
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	return (1);
}
