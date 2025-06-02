#include "../minishell.h"

int	handle_token(char *command, int *i, t_token **tokens_list)
{
	t_ints	ints;	
	t_qtype	q_type;

	ints.start = *i;
	q_type = quote_type(command[ints.start]);
	while (command[*i] && command[*i] != ' ' && !is_operator(command[*i])
		&& command[*i] != '\'' && command[*i] != '\"')
		(*i)++;
	ints.end = *i;
	if (*i > ints.start)
	{
		if (!add_to_list(command, ints, tokens_list, q_type))
			return (0);
	}
	return (1);
}

int	is_space_or_operator(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
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

int	is_redirect(t_ttype type)
{	
	if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT
		|| type == T_APPEND || type == T_HEREDOC)
		return (1);
	else
		return (0);
}
