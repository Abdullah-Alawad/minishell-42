#include "../minishell.h"

int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
		return (0);
	}
	else
	{
		perror("getcwd");
		return (1);
	}
}
