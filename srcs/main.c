#include "../minishell.h"


void	print_command_list(t_command *cmd)
{
	int i;

	while (cmd)
	{
		printf("Arguments:\n");
		if (cmd->av)
		{
			i = 0;
			while (cmd->av[i])
			{
				printf("  av[%d]: %s\n", i, cmd->av[i]);
				i++;
			}
		}
		printf("here array:\n");
		if (cmd->here_arr)
		{
			i = 0;
			while (cmd->here_arr[i])
			{
				printf("  av[%d]: %s\n", i, cmd->here_arr[i]);
				i++;
			}
		}
		printf("Input File: %s\n", cmd->in_file ? cmd->in_file : "NULL");
		printf("Output File: %s\n", cmd->out_file ? cmd->out_file : "NULL");
		printf("Pipe: %d\n", cmd->pipe);
		printf("Heredoc: %d\n", cmd->heredoc);
		printf("Append: %d\n", cmd->append);
		printf("Is Builtin: %d\n", cmd->is_builtin);
		printf("----------------------\n");
		cmd = cmd->next;
	}
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
	exit(1);
}

void	error_cmd_list(t_env_list **env, t_token **tokens, char *command)
{
	free_env_list(env);
	free_tokens(tokens);
	free(command);
	exit(1);
}

t_command*	create_and_parse_tokens(char *command, int *status, t_env_list *env_lst)
{
	t_token		*tokens_list;
	t_command	*cmds_list;

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

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_env_list	*env_lst;
	static int	status;
	t_command	*cmds_list;

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
		cmds_list = create_and_parse_tokens(command, &status, env_lst);
		//print_command_list(cmds_list);
		if (cmds_list)
		{
			execute_command(cmds_list, &status, &env_lst);
			free_commands(&cmds_list);
		}
		free(command);
	}
	return (0);
}
