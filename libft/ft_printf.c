/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:38:27 by aalawad           #+#    #+#             */
/*   Updated: 2024/10/03 14:36:21 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_onechar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *s)
{
	int		len;
	char	*null_str;

	len = 0;
	if (s == NULL)
	{
		null_str = "(null)";
		while (null_str[len])
		{
			write (1, &null_str[len], 1);
			len++;
		}
		return (len);
	}
	while (s[len] != '\0')
	{
		write(1, &s[len], 1);
		len++;
	}
	return (len);
}

int	ft_printnumber(int num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa(num);
	len = ft_printstr(str);
	if (str)
		free(str);
	return (len);
}

int	ft_formats(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_onechar(va_arg(args, int));
	else if (format == 's')
		len += ft_printstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		len += ft_printnumber(va_arg(args, int));
	else if (format == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == '%')
	{
		write (1, "%", 1);
		len++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			len += ft_onechar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
