/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:39:58 by aalawad           #+#    #+#             */
/*   Updated: 2024/08/28 13:59:30 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The code of allocating zeros can be deleted and only use bzero or memset

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*mem;

	total = nmemb * size;
	mem = (void *)malloc(total);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, total);
	return (mem);
}
/*
int main(void)
{
	void	*ptr = ft_calloc(10, 1);
	
	if (!ptr)
		printf("allocation failed");
		
	char c = 'A';
	size_t i = 0;
	char	*s = (char *)ptr;
	while (i < 10)
	{
		s[i] = c;
		c++;
		i++;
	}
	printf("%s\n", s);
	free(ptr);
}
*/
