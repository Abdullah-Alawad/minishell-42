/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:23 by aalawad           #+#    #+#             */
/*   Updated: 2024/10/03 13:42:05 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc(len + 1);
	if (!num)
		return (NULL);
	num[len] = '\0';
	len--;
	while (n != 0)
	{
		num[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (num);
}

int	ft_print_unsigned(unsigned int n)
{
	int		len;
	char	*num;

	len = 0;
	if (n == 0)
	{
		len++;
		write(1, "0", 1);
	}
	else
	{
		num = ft_uitoa(n);
		while (num[len])
		{
			write(1, &num[len], 1);
			len++;
		}
		if (num)
			free (num);
	}
	return (len);
}
