/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:50:40 by machrist          #+#    #+#             */
/*   Updated: 2024/01/16 13:59:16 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	print_format(int fd, char specifier, va_list args)
{
	char	*hex;
	char	*up_hex;

	hex = "0123456789abcdef";
	up_hex = "0123456789ABCDEF";
	if (specifier == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_base_fd(va_arg(args, int), 10, "0123456789", fd));
	else if (specifier == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), 10, hex, fd));
	else if (specifier == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), 16, hex, fd));
	else if (specifier == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), 16, up_hex, fd));
	else if (specifier == 'p')
		return (ft_test_ptr(va_arg(args, unsigned long long), fd));
	return (ft_putchar_fd(specifier, fd));
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		count;
	int		tmp;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			tmp = print_format(fd, *++format, args);
		else
			tmp = ft_putchar_fd(*format, fd);
		if (tmp == -1)
		{
			va_end(args);
			return (-1);
		}
		count += tmp;
		++format;
	}
	va_end(args);
	return (count);
}
