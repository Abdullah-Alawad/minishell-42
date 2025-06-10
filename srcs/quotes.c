#include "../minishell.h"

int	good_quotes(char *command)
{
	int		i;
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (command[i])
	{
		if (command[i] == '\"')
			d_quote = !d_quote;
		else if (command[i] == '\'')
			s_quote = !s_quote;
		i++;
	}
	return (!d_quote && !s_quote);
}

t_qtype	quote_type(char q)
{
	if (q == '\"')
		return (DOUBLE_Q);
	else if (q == '\'')
		return (SINGLE_Q);
	return (NO_Q);
}

int	handle_quotes(char *command, int start, t_token **tokens_list)
{
	char	q;
	t_ints	ints;
	t_qtype	q_type;

	q = command[start];
	q_type = quote_type(q);
	start += 1;
	ints.start = start;
	ints.end = start;
	while (command[ints.end] && command[ints.end] != q)
		ints.end++;
	if (!add_to_list(command, ints, tokens_list, q_type))
		return (-1);
	ints.end++;
	return (ints.end);
}
