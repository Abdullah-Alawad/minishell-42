/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:13 by aal-joul          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:13 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_char_to_result(char *data, t_expand *ex)
{
	char	buff[2];

	buff[0] = data[ex->i];
	buff[1] = '\0';
	ex->result = ft_strjoin_and_free(ex->result, buff);
	ex->i++;
}

void	handel_s_q(char *data, t_expand *ex)
{
	append_char_to_result(data, ex);
	while (data[ex->i] && data[ex->i] != '\'')
		append_char_to_result(data, ex);
	if (data[ex->i] == '\'')
	{
		append_char_to_result(data, ex);
	}
}

void	handel_d_q(char *data, t_expand *ex)
{
	append_char_to_result(data, ex);
	while (data[ex->i] && data[ex->i] != '"')
	{
		if (data[ex->i] == '$')
		{
			ex->i++;
			handle_dollar(data, ex);
		}
		else
			append_char_to_result(data, ex);
	}
	if (data[ex->i] == '"')
	{
		append_char_to_result(data, ex);
	}
}

void	do_expand(char *data, t_expand *ex)
{
	while (data[ex->i])
	{
		if (data[ex->i] == '\'')
			handel_s_q(data, ex);
		else if (data[ex->i] == '"')
			handel_d_q(data, ex);
		else if (data[ex->i] == '$')
		{
			ex->i++;
			handle_dollar(data, ex);
		}
		else
			append_char_to_result(data, ex);
	}
}

char	*expander(char *data, t_env_list *env_lst, int status, char **args)
{
	t_expand	*ex;
	char		*final_result;

	ex = malloc(sizeof(t_expand));
	if (!ex)
		return (NULL);
	ex->env_lst = env_lst;
	ex->status = status;
	ex->args = args;
	ex->result = ft_strdup("");
	ex->i = 0;
	do_expand(data, ex);
	final_result = ft_strdup(ex->result);
	free(ex->result);
	free(ex);
	free(data);
	return (final_result);
}
