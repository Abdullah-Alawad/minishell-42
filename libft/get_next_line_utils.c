/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:53:33 by aalawad           #+#    #+#             */
/*   Updated: 2024/11/04 10:53:41 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_copy(char *line, char *buffer, int i)
{
	int		j;

	j = 0;
	while (buffer[i] != '\0')
		line[j++] = buffer[i++];
	free(buffer);
}
