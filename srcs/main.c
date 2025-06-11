#include "../minishell.h"

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

t_command*	create_and_parse_tokens(char *command, int *status, t_env_list *env_lst)
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
		if (execute_command(cmds_list, status, &env_lst) == -1)
		{
			free_commands(&cmds_list);
			free_env_list(&env_lst);
			free(command);
			rl_clear_history();
			exit (1);
		}
		free_commands(&cmds_list);
	}
	free(command);
}

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_env_list	*env_lst;
	static int	status;

	env_lst = create_env_list(env);
	if (!env_lst)
		return (1);
	while (FOREVER)
	{
		command = readline(GREEN"minishell42"RESET"$ ");
		if (!command)
			error_cmd(&env_lst, ac);
		add_history(command);
		command = expander(command, env_lst, status, av);
		if (!command)
			continue ;
		execution(command, &status, env_lst);
	}
}
