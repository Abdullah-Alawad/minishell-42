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

