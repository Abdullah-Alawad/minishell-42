/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:11:46 by aalawad           #+#    #+#             */
/*   Updated: 2024/10/03 14:19:25 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int num, char format)
{
	int	len;

	len = 0;
	if (num >= 16)
		len += ft_print_hex(num / 16, format);
	if (num % 16 <= 9)
	{
		ft_putchar_fd((num % 16 + '0'), 1);
		len++;
	}
	else
	{
		if (format == 'x')
		{
			ft_putchar_fd((num % 16 - 10 + 'a'), 1);
			len++;
		}
		else
		{
			ft_putchar_fd((num % 16 - 10 + 'A'), 1);
			len++;
		}
	}
	return (len);
}
