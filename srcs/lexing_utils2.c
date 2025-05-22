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
