#include "../minishell.h"

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


t_command	*cmd_create(int status)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = malloc(sizeof(char *) * 1);
	if (!cmd->av)
		return (NULL);
	cmd->av[0] = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->pipe = 0;
	cmd->heredoc = 0;
	cmd->append = 0;
	cmd->is_builtin = 0;
	cmd->status = status;
	cmd->next = NULL;
	return (cmd);
}

t_command	*cmds_lst_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmds_add_back(t_command **cmds_list, t_command *cmd)
{
	if (!cmds_list)
		return ;
	if (!*cmds_list)
		*cmds_list = cmd;
	else
		(cmds_lst_last(*cmds_list))->next = cmd;
}
