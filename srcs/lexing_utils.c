/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:23:38 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:23:40 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ttype	token_type(char *data)
{
	if (!data || !*data)
		return (T_DATA);
	else if (data[0] == '<' && data[1] && data[1] == '<')
		return (T_HEREDOC);
	else if (data[0] == '>' && data[1] && data[1] == '>')
		return (T_APPEND);
	else if (data[0] == '<')
		return (T_REDIRECT_IN);
	else if (data[0] == '>')
		return (T_REDIRECT_OUT);
	else if (data[0] == '|')
		return (T_PIPE);
	return (T_DATA);
}

t_token	*new_token(char	*data, t_ttype t_type, t_qtype q_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = data;
	token->type = t_type;
	token->quote_type = q_type;
	token->next = NULL;
	return (token);
}

t_token	*tokens_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	tokens_add_back(t_token **tokens_list, t_token *token)
{
	if (!tokens_list)
		return ;
	if (!*tokens_list)
		*tokens_list = token;
	else
		(tokens_last(*tokens_list))->next = token;
}

int	add_to_list(char *command, t_ints ints,
				t_token **tokens_list, t_qtype q_type)
{
	t_token	*token;
	char	*data;
	t_ttype	t_type;

	data = ft_substr(command, ints.start, ints.end - ints.start);
	if (!data)
	{
		free_tokens(tokens_list);
		return (0);
	}
	if (q_type == NO_Q)
		t_type = token_type(data);
	else
		t_type = T_DATA;
	token = new_token(data, t_type, q_type);
	if (!token)
	{
		free(data);
		free_tokens(tokens_list);
		return (0);
	}
	tokens_add_back(tokens_list, token);
	return (1);
}
