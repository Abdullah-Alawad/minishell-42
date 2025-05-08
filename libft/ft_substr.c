/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:37:01 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/03 11:38:11 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	srclen;
	size_t	i;

	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	i = 0;
	if (start == 4294967295)
	{
		str = (char *)malloc(1);
		if (!str)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if (start < srclen)
		i = srclen - start;
	if (i > len)
		i = len;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, i + 1);
	return (str);
}
/*
int main(void)
{
	char *str = "hello, world, MEAWWWWW";
	char *sub = ft_substr(str, 7, 12);
	printf("%s\n", sub);
}
*/
