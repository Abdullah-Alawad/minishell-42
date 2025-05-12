#include "../minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Data: %s\n", tokens->data);
		printf("Type: %d\n", tokens->type);
		printf("Quote Type: %d\n", tokens->quote_type);
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

	(void)av;
	(void)ac;
	env_lst = create_env_list(env);
	if (!env_lst)
		return (1);

	t_env_list	*tmp;
	tmp = env_lst;
	while (tmp)
	{
		printf("len: %d\n", tmp->len);
		tmp = tmp->next;
	}
	

	while (FOREVER)
	{
		command = readline(GREEN"minishell42"RESET"$ ");
		if (!command)
		{
			rl_clear_history();
			exit(1);
		}
		add_history(command);
		tokens_list = handle_command(command, &status);
		if (!tokens_list)
			printf("exit status: %d\n", status);
		print_tokens(tokens_list);
		// frees so far
		free(command);
		free_tokens(&tokens_list);
		if (env_lst)
			free_env_list(&env_lst);
	}
	return (0);
}
