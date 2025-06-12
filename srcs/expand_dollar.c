#include "../minishell.h"

void	expand_positional_parameter(char *data, t_expand *ex)
{
	int	len;

	ex->start = ex->i;
	while (ft_isdigit(data[ex->i]))
		ex->i++;
	len = ex->i - ex->start;
	if (len == 0)
		return ;
	ex->var_name = ft_substr(data, ex->start, len);
	if (!ex->var_name || ex->var_name[0] == '\0'
		|| !ft_isdigit(ex->var_name[0]))
	{
		free(ex->var_name);
		return ;
	}
	ex->value = get_positional_value(ex->var_name, ex->args, ex->status);
	if (ex->is_redirection_context
		&& ex->value && contains_whitespace(ex->value))
		ex->ambiguous_redirect = 1;
	if (ex->value)
		ex->result = ft_strjoin_and_free(ex->result, ex->value);
	else
		ex->result = ft_strjoin_and_free(ex->result, "");
	free(ex->var_name);
}

void	expand_named_variable(char *data, t_expand *ex)
{
	ex->start = ex->i;
	while (ft_isalnum(data[ex->i]) || data[ex->i] == '_')
		ex->i++;
	ex->var_name = ft_substr(data, ex->start, ex->i - ex->start);
	ex->value = get_env_value(ex->var_name, ex->env_lst);
	if (ex->is_redirection_context
		&& ex->value && contains_whitespace(ex->value))
		ex->ambiguous_redirect = 1;
	if (ex->value)
		ex->result = ft_strjoin_and_free(ex->result, ex->value);
	else
		ex->result = ft_strjoin_and_free(ex->result, "");
	free(ex->var_name);
}

void	expand_dollar_with_digits(char *data, t_expand *ex)
{
	char	buff[2];

	buff[0] = data[ex->i];
	buff[1] = '\0';
	ex->i++;
	ex->value = get_positional_value(buff, ex->args, ex->status);
	if (ex->is_redirection_context
		&& ex->value && contains_whitespace(ex->value))
		ex->ambiguous_redirect = 1;
	if (ex->value)
		ex->result = ft_strjoin_and_free(ex->result, ex->value);
	else
		ex->result = ft_strjoin_and_free(ex->result, "");
	while (ft_isdigit(data[ex->i]))
	{
		buff[0] = data[ex->i];
		buff[1] = '\0';
		ex->result = ft_strjoin_and_free(ex->result, buff);
		ex->i++;
	}
}

void	handle_dollar(char *data, t_expand *ex)
{
	if (data[ex->i] == ' ' || data[ex->i] == '\0')
	{
		ex->i--;
		append_char_to_result(data, ex);
	}
	else if (data[ex->i] == '{')
		expand_braced_variable(data, ex);
	else if (data[ex->i] == '?')
		expand_status_variable(ex);
	else if (ft_isdigit(data[ex->i]))
	{
		expand_dollar_with_digits(data, ex);
	}
	else if (ft_isalpha(data[ex->i]) || data[ex->i] == '_')
		expand_named_variable(data, ex);
	else
	{
		ex->i--;
		append_char_to_result(data, ex);
	}
}
