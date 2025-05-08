/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:57:35 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/09 12:57:37 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	num_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static char	*transform(char *s, unsigned int num, long int len)
{
	while (num > 0)
	{
		s[len] = '0' + (num % 10);
		num = num / 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char				*str;
	long int			len;
	unsigned int		num;

	len = num_len(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
		num = n;
	str = transform(str, num, len);
	return (str);
}
/*
int main(void)
{
	int	n;
	char	*res;
	
	n = -45632;
	res = ft_itoa(n);
	printf("%s\n", res);
	
	free(res);
}
*/
