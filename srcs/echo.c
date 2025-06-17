/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:21:58 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:22:00 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flag(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	handle_echo(char **cmd)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (cmd[i] && check_flag(cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
