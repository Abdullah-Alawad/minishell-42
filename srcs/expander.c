#include "../minishell.h"

char	*expander(char *data, t_env_list *env, int status)
{
	(void)data;
	(void)env;
	printf ("status: %d\n", status);
	return (ft_strdup(data));
}