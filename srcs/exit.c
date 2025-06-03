#include "../minishell.h"

int	is_num(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '+' || num[0] == '-')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	handle_exit(t_env_list **env, t_command **cmd, int status)
{
	int	e_status;

	e_status = status;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd && cmd[0]->av[1])
	{
		if (!is_num(cmd[0]->av[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[0]->av[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			e_status = 2;
		}
		else if (cmd[0]->av[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		else
			e_status = ft_atoi(cmd[0]->av[1]);
	}
	free_commands(cmd);
	free_env_list(env);
	exit(e_status % 256);
}
