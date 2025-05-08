/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:01:03 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/16 11:38:04 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
int main(void)
{
	char	s[10] = "AAAAAAAAAA";
	size_t	i;

	i = 0;
	while (i < sizeof(s))
		printf("%c ", s[i++]);
	printf("\n");
	i = 0;
	ft_bzero(s, sizeof(s));
	while (i < sizeof(s))
		printf("%c,", s[i++]);
	printf("\n");
}
*/
