/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:25:50 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:25:52 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_expand_error(char *cmd, t_env_list **env, t_expand **ex)
{
	free(cmd);
	free_env_list(env);
	rl_clear_history();
	if (ex)
	{
		if (*ex)
		{
			if ((*ex)->result)
				free((*ex)->result);
			free(*ex);
		}
	}
	exit(1);
}

void	error_cmd(t_env_list **env, int ac)
{
	(void)ac;
	free_env_list(env);
	rl_clear_history();
	exit(1);
}

void	error_tokens(t_env_list **env, char *command)
{
	free_env_list(env);
	free(command);
	rl_clear_history();
	exit(1);
}

void	error_cmd_list(t_env_list **env, t_token **tokens, char *command)
{
	free_env_list(env);
	free_tokens(tokens);
	free(command);
	rl_clear_history();
	exit(1);
}

int	spaces_only(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
