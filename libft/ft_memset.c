/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:57:00 by aalawad           #+#    #+#             */
/*   Updated: 2024/08/28 14:40:57 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int main(void)
{
	char	ptr[10];
	
	ft_memset((void *)ptr, 'A', 10);
	int i = 0;
	while (i < 10)
	{
		printf("%c ", ptr[i]);
		i++;
	}
	printf("\n");
}
*/
