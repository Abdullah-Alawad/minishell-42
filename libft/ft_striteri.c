/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:34:43 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/03 11:35:25 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	addone(unsigned int i, char *s)
{
		if (s[i] >= 97 && s[i] <= 122)
			s[i] -= 32;
}

int main(void)
{
	char	s[] = "heloooooooo";
	ft_striteri(s, addone);
	printf("%s\n", s);
}
*/
