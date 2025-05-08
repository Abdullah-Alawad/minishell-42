/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:28 by aalawad           #+#    #+#             */
/*   Updated: 2024/09/03 11:36:29 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	digit;

	nb = n;
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	digit = (nb % 10) + '0';
	write(fd, &digit, 1);
}
/*
int main(void)
{
	printf("%d\n", -1234253);
}
*/
