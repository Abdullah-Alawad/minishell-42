/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:23:28 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:23:30 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_qtype	q_type;

	ints.end = start;
	ints.start = start;
	q_type = quote_type(command[start]);
	if ((command[ints.start] == '<' && command[ints.start + 1] == '<')
		|| (command[ints.start] == '>' && command[ints.start + 1] == '>'))
		ints.end += 2;
	else
		ints.end += 1;
	if (!add_to_list(command, ints, tokens_list, q_type))
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
			i = handle_combined_token(command, i, tokens_list);
			if (i == -1)
				return (0);
		}
	}
	if (i == -1)
		return (0);
	return (1);
}

int	check_tokens(t_token *tokens_list)
{
	if (!tokens_list || tokens_list->type == T_PIPE)
		return (0);
	while (tokens_list)
	{
		if (tokens_list->type == T_PIPE)
		{
			if (!tokens_list->next || (tokens_list->next->type != T_DATA
					&& !is_redirect(tokens_list->next->type)))
				return (0);
		}
		if (is_redirect(tokens_list->type))
		{
			if (!tokens_list->next || tokens_list->next->type != T_DATA)
				return (0);
		}
		tokens_list = tokens_list->next;
	}
	return (1);
}

t_token	*handle_command(char *command, int *status)
{
	t_token	*tokens_list;

	(void)status;
	tokens_list = NULL;
	if (!lexer(command, &tokens_list))
	{
		ft_putstr_fd("[ERROR]: failed mallocs\n", STDERR_FILENO);
		return (NULL);
	}
	return (tokens_list);
}
