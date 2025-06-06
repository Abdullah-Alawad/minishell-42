#include "../minishell.h"

int contains_whitespace(const char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			return (1);
		str++;
	}
	return (0);
}

void	setup_expand(t_expand *ex, t_env_list *env, int status, char **args)
{
	ex->env_lst = env;
	ex->status = status;
	ex->args = args;
	ex->i = 0;
	ex->ambiguous_redirect = 0;
	ex->is_redirection_context = 0;
}