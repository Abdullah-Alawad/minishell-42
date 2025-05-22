#include "../minishell.h"

int handle_echo(char **cmd)
{
	int	i;
	int	new_line;
    
	new_line = 0;
	if (ft_strncmp("-n", cmd[1], ft_strlen(cmd[1])) == 0)
		i = 2;
	else
	{
		new_line = 1;
		i = 1;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}