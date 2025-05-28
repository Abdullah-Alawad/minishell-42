#include "../minishell.h"

int	copy_here(t_command *cmd, char **new_here, int *i)
{
	*i = 0;
	while (cmd->here_arr && cmd->here_arr[*i])
	{
		new_here[*i] = ft_strdup(cmd->here_arr[*i]);
		if (!new_here[*i])
		{
			free_av(new_here);
			return (0);
		}
		(*i)++;
	}
	free_av(cmd->here_arr);
	return (1);
}

int	copy_av(t_command *cmd, char **new_av, int *i)
{
	*i = 0;
	while (cmd->av && cmd->av[*i])
	{
		new_av[*i] = ft_strdup(cmd->av[*i]);
		if (!new_av[*i])
		{
			free_av(new_av);
			return (0);
		}
		(*i)++;
	}
	free_av(cmd->av);
	return (1);
}

int	set_here_arr(t_command *cmd, char *del)
{
	char	**new_here;
	int		i;

	i = 0;
	while (cmd->here_arr && cmd->here_arr[i])
		i++;
	new_here = malloc(sizeof(char *) * (i + 2));
	if (!new_here)
		return (0);
	if (!copy_here(cmd, new_here, &i))
		return(0);
	new_here[i] = ft_strdup(del);
	if (!new_here[i])
	{
		free(new_here);
		return (0);
	}
	new_here[i + 1] = NULL;
	cmd->here_arr = new_here;
	return (1);
}

t_command	*cmd_create(int status)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = malloc(sizeof(char *) * 1);
	if (!cmd->av)
		return (NULL);
	cmd->here_arr = malloc(sizeof(char *) * 1);
	if (!cmd->here_arr)
		return(NULL);
	cmd->av[0] = NULL;
	cmd->here_arr[0] = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	cmd->pipe = 0;
	cmd->heredoc = 0;
	cmd->append = 0;
	cmd->is_builtin = 0;
	cmd->status = status;
	cmd->next = NULL;
	return (cmd);
}

