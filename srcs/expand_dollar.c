#include "../minishell.h"

void	expand_braced_variable(char *data, t_expand *ex)
{
	ex->i++;
	ex->start = ex->i;
	while (data[ex->i] && data[ex->i] != '}')
		ex->i++;
	ex->var_name = ft_substr(data, ex->start, ex->i - ex->start);
	if (ft_isdigit(ex->var_name[0]))
		ex->value = get_positional_value(ex->var_name, ex->args);
	else
		ex->value = get_env_value(ex->var_name, ex->env_lst);
	if (ex->value)
		ex->result = ft_strjoin_and_free(ex->result, ex->value);
	else
		ex->result = ft_strjoin_and_free(ex->result, "");
	free(ex->var_name);
	if (data[ex->i] == '}')
		ex->i++;
}

void	expand_status_variable(t_expand *ex)
{
	char	*status_str;

	ex->i++;
	status_str = ft_itoa(ex->status);
	ex->result = ft_strjoin_and_free(ex->result, status_str);
	free(status_str);
}

void	expand_positional_parameter(char *data, t_expand *ex)
{
	ex->start = ex->i;
	while (ft_isdigit(data[ex->i]))
		ex->i++;
	ex->var_name = ft_substr(data, ex->start, ex->i - ex->start);
	ex->value = get_positional_value(ex->var_name, ex->args);
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
	if (ex->value)
		ex->result = ft_strjoin_and_free(ex->result, ex->value);
	else
		ex->result = ft_strjoin_and_free(ex->result, "");
	free(ex->var_name);
}

void	handle_dollar(char *data, t_expand *ex)
{
	if (data[ex->i] == ' ' || data[ex->i] == '\0') // for case $ alone
	{	
		ex->i--;
		append_char_to_result(data, ex);
	}
	else if (data[ex->i] == '{')
		expand_braced_variable(data, ex);
	else if (data[ex->i] == '?')
		expand_status_variable(ex);
	else if (ft_isdigit(data[ex->i]))
		expand_positional_parameter(data, ex);
	else if (ft_isalpha(data[ex->i]) || data[ex->i] == '_')
		expand_named_variable(data, ex);
	else										// for "$" case
	{
		ex->i--;
		append_char_to_result(data, ex);
	}
}
