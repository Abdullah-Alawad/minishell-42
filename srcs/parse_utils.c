#include "../minishell.h"

char	**add_new_av(char **new_av, int i, char *data, t_qtype q_type)
{
	if ((q_type == NO_Q || q_type == DOUBLE_Q) && ft_strchr(data, '$'))
		new_av[i] = ft_strdup("expand string"); // Expander function HERE
	else
		new_av[i] = ft_strdup(data);
	if (!new_av[i])
	{
		free_av(new_av);
		return (NULL);
	}
	new_av[i + 1] = NULL;
	return (new_av);
}

t_command	*cmd_create(void)
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
