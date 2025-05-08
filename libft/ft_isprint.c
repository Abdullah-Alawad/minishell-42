/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:31:50 by aalawad           #+#    #+#             */
/*   Updated: 2024/08/26 10:33:54 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int main(void)
{
	char	c;
	
	c = '\n';
	if (ft_isprint(c))
		printf("is printable\n");
	else
		printf("not printable\n");
}
*/
