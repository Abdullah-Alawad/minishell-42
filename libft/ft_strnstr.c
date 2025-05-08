/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:45 by aalawad           #+#    #+#             */
/*   Updated: 2024/08/28 13:20:11 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*b;
	const char	*l;
	size_t		rem;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (*big != '\0' && len >= 1)
	{
		b = big;
		l = little;
		rem = len;
		while (*b == *l && *l != '\0' && rem > 0)
		{
			b++;
			l++;
			rem--;
		}
		if (*l == '\0')
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
/*
int main(void)
{
	char s[] = "Hello, world again";
	printf("%s\n", ft_strnstr(s, "world", 13));
}
*/
