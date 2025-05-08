/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:35:57 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/03 11:35:58 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	tolow(unsigned int i, char c)
{
	if (i % 2 == 0)
		if (c >= 65 && c <= 90)
			return (c + 32);
	return (c);
}

int main(void)
{
	char s[] = "MEAWWWWW";
	char *r = ft_strmapi(s, tolow);
	printf("%s\n", r);
}
*/
