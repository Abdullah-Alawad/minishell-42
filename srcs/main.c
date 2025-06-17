/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:23:20 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:23:22 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_and_parse_tokens(char *command, int *status,
		t_env_list *env_lst)
{
	t_token		*tokens_list;
	t_command	*cmds_list;

	if (!good_quotes(command))
	{
		ft_putstr_fd("-minishll: syntax error\n", STDERR_FILENO);
		*status = 2;
		return (NULL);
	}
	tokens_list = handle_command(command, status);
	if (!tokens_list)
		error_tokens(&env_lst, command);
	if (valid_command(tokens_list, status))
	{
		cmds_list = parse_tokens(tokens_list, env_lst, status);
		if (!cmds_list)
			error_cmd_list(&env_lst, &tokens_list, command);
		free_tokens(&tokens_list);
		return (cmds_list);
	}
	else
		return (NULL);
}

void	execution(char *command, int *status, t_env_list *env_lst)
{
	t_command	*cmds_list;

	cmds_list = create_and_parse_tokens(command, status, env_lst);
	if (cmds_list)
	{
		free(command);
		if (execute_command(cmds_list, status, &env_lst) == -1)
		{
			free_commands(&cmds_list);
			free_env_list(&env_lst);
			rl_clear_history();
			exit (1);
		}
		free_commands(&cmds_list);
	}
	else
		free(command);
}

void	continue_command(char *cmd)
{
	if (cmd)
		free(cmd);
}

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_env_list	*env_lst;
	static int	status;

	env_lst = create_env_list(env);
	if (!env_lst)
		return (1);
	setup_signals();
	while (FOREVER)
	{
		command = readline(GREEN"minishell42"RESET"$ ");
		if (!command)
			ctrl_d(&env_lst, status, ac);
		if (g_s)
			status_update(&status);
		add_history(command);
		command = expander(command, env_lst, status, av);
		if (!command || !command[0])
		{
			continue_command(command);
			continue ;
		}
		execution(command, &status, env_lst);
	}
}
