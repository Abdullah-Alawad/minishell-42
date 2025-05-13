#include "../minishell.h"

char	*expander(char *data, t_env_list *env)
{
	(void)data;
	(void)env;
	return (ft_strdup(data));
}