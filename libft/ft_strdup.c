/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:59:10 by aalawad           #+#    #+#             */
/*   Updated: 2024/08/28 15:04:41 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	while (s[i] != '\0')
		i++;
	dup = (char *)malloc(i + 1);
	if (dup == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}
/*
int main(void)
{
	char *s;
	
	s = ft_strdup("Meawwwwwww");
	printf("%s\n", s);
	free(s);
}
*/
