#include "../minishell.h"

int	add_token_with_data(char *data, t_token **tokens_list, t_qtype q_type)
{
	t_token	*token;
	t_ttype	t_type;

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

char	*str_append_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*extract_quoted_part(char *cmd, int *i, t_qtype *q_type)
{
	int		start;
	char	quote;
	char	*result;

	quote = cmd[*i];
	if (quote == '\'')
		*q_type = SINGLE_Q;
	else if (quote == '"')
		*q_type = DOUBLE_Q;
	start = ++(*i);
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	result = ft_substr(cmd, start, *i - start);
	if (cmd[*i] == quote)
		(*i)++;
	return (result);
}

char	*extract_unquoted_part(char *cmd, int *i)
{
	int		start;
	char	*part;

	start = *i;
	while (cmd[*i] && !is_space_or_operator(cmd[*i])
		&& cmd[*i] != '\'' && cmd[*i] != '"')
		(*i)++;
	part = ft_substr(cmd, start, *i - start);
	return (part);
}

int	handle_combined_token(char *cmd, int i, t_token **tokens_list)
{
	char	*token_str;
	char	*part;
	t_qtype	q_type;

	token_str = NULL;
	q_type = NO_Q;
	while (cmd[i] && !is_space_or_operator(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			part = extract_quoted_part(cmd, &i, &q_type);
		else
			part = extract_unquoted_part(cmd, &i);
		if (!part)
		{
			free(token_str);
			return (-1);
		}
		token_str = str_append_and_free(token_str, part);
	}
	if (!add_token_with_data(token_str, tokens_list, q_type))
		return (-1);
	return (i);
}
