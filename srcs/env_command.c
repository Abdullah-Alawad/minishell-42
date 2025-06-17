/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:25:23 by aalawad           #+#    #+#             */
/*   Updated: 2025/06/17 16:25:25 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_env(t_env_list **env)
{
	t_env_list	*head;

	head = *env;
	while (head)
	{
		if (head->exported == 0)
			printf("%s=%s\n", head->key, head->data);
		else if (head->exported == 1)
			printf("%s=\n", head->key);
		head = head->next;
	}
	return (0);
}
