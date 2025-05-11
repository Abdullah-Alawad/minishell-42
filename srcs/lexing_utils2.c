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
