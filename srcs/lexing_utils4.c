/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:24:01 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:24:02 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_command(t_token *tokens, int *status)
{
	if (!check_tokens(tokens))
	{
		free_tokens(&tokens);
		ft_putstr_fd("-minishell: syntax error\n", STDERR_FILENO);
		*status = 2;
		return (0);
	}
	else
		return (1);
}
