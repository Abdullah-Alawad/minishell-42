#include "../minishell.h"

int	handle_token(char *command, int *i, t_token **tokens_list)
{
	t_ints	ints;	

	ints.start = *i;
	while (command[*i] && command[*i] != ' ' && !is_operator(command[*i]))
		(*i)++;
	ints.end = *i;
	if (*i > ints.start)
	{
		if (!add_to_list(command, ints, tokens_list))
			return (0);
	}
	return (1);
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