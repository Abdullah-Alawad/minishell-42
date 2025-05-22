#include "../minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_operator(char *command, int start, t_token **tokens_list)
{
	t_ints	ints;

	ints.end = start;
	ints.start = start;
	if ((command[ints.start] == '<' && command[ints.start + 1] == '<')
		|| (command[ints.start] == '>' && command[ints.start + 1] == '>'))
		ints.end += 2;
	else
		ints.end += 1;
	if (!add_to_list(command, ints, tokens_list))
		return (-1);
	return (ints.end);
}

int	lexer(char *command, t_token **tokens_list)
{
	int		i;

	i = 0;
	while (command[i] && i >= 0)
	{
		while (command[i] && command[i] == ' ')
			i++;
		if (command[i] && is_operator(command[i]))
			i = check_operator(command, i, tokens_list);
		else if (command[i])
		{
			if (!handle_token(command, &i, tokens_list))
				return (0);
		}
	}
	if (i == -1)
		return (0);
	return (1);
}

int	check_tokens(t_token *tokens_list)
{
	if (!tokens_list)
		return (0);
	if (tokens_list->type == T_PIPE)
		return (0);
	while (tokens_list)
	{
		if (tokens_list->type != T_DATA)
		{
			if (tokens_list->next == NULL)
				return (0);
			if (tokens_list->next->type != T_DATA)
				return (0);
		}
		tokens_list = tokens_list->next;
	}
	return (1);
}

t_token	*handle_command(char *command, int *status)
{
	t_token	*tokens_list;

	tokens_list = NULL;
	if (good_quotes(command))
	{
		if (!lexer(command, &tokens_list))
		{
			printf(RED"[ERROR], faild mallocs\n"RESET);
			return (NULL);
		}
		if (!check_tokens(tokens_list))
		{
			free_tokens(&tokens_list);
			printf(RED"[ERROR], syntax error\n"RESET);
			*status = 2;
			return (NULL);
		}
		return (tokens_list);
	}
	else
	{
		*status = 2;
		return (NULL);
	}
}
