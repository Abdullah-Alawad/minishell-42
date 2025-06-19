/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:35:00 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/19 15:35:02 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_expand_heredoc(char *data, t_expand *ex)
{
	int	j;

	while (data[ex->i])
	{
		if (data[ex->i] == '\'')
			handel_d_q(data, ex);
		else if (data[ex->i] == '"')
			handel_d_q(data, ex);
		else if (data[ex->i] == '$')
		{
			j = ex->i - 1;
			while (j >= 0 && (data[j] == ' ' || data[j] == '\t'))
				j--;
			if (j >= 0 && (data[j] == '>' || data[j] == '<'))
				ex->is_redirection_context = 1;
			else
				ex->is_redirection_context = 0;
			ex->i++;
			handle_dollar(data, ex);
		}
		else
			append_char_to_result(data, ex);
	}
}

char	*heredoc_expander(char *data, t_env_list *env_lst,
		int status, char **args)
{
	t_expand	*ex;
	char		*final_result;

	ex = malloc(sizeof(t_expand));
	if (!ex)
		exit_expand_error(data, &env_lst, NULL);
	setup_expand(ex, env_lst, status, args);
	ex->result = ft_strdup("");
	if (!ex->result)
		exit_expand_error(data, &env_lst, &ex);
	do_expand_heredoc(data, ex);
	final_result = ft_strdup(ex->result);
	if (!final_result)
		exit_expand_error(data, &env_lst, &ex);
	if (ex->ambiguous_redirect)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		free(final_result);
		final_result = NULL;
	}
	free(ex->result);
	free(ex);
	free(data);
	return (final_result);
}
