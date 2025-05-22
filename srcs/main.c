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

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Data: %s\n", tokens->data);
		printf("Type: %d\n", tokens->type);
		printf("-----\n");
		tokens = tokens->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_env_list	*env_lst;
	static int	status;
	t_token		*tokens_list;
	t_command	*cmds_list;

	(void)ac;
	env_lst = create_env_list(env);
	if (!env_lst)
		return (1);
	status = 7;
	while (FOREVER)
	{
		command = readline(GREEN"minishell42"RESET"$ ");
		if (!command)
		{
			rl_clear_history();
			exit(1);
		}
		add_history(command);

		command = expander(command, env_lst, status, av);
		printf("expanded: %s\n", command);
		tokens_list = handle_command(command, &status);
		if (!tokens_list)
			printf("exit status: %d\n", status);
		
		cmds_list = parse_tokens(tokens_list, env_lst, &status);
		//print_command_list(cmds_list);
		execute_command(cmds_list, command, &status, &env_lst);
		free_commands(&cmds_list);
		free(command);
		free_tokens(&tokens_list);
	}
	if (env_lst)
		free_env_list(&env_lst);
	return (0);
}
