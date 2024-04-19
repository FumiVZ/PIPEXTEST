/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:23:05 by machrist          #+#    #+#             */
/*   Updated: 2024/01/16 13:46:45 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_ptr(unsigned long long ptr, int len_base, char *base, int fd)
{
	int		count;
	int		tmp;
	char	buffer[128];
	int		s;

	count = 0;
	s = 0;
	if (ptr == 0)
		buffer[count++] = '0';
	while (ptr != 0)
	{
		buffer[count++] = base[ptr % len_base];
		ptr = ptr / len_base;
	}
	tmp = count;
	while (--tmp >= 0)
		if (ft_putchar_fd(buffer[tmp], fd) == -1)
			return (-1);
	return (count + s);
}

int	ft_test_ptr(unsigned long long ptr, int fd)
{
	int	count;

	if (ptr == 0)
		return (ft_putstr_fd("(nil)", fd));
	if (ft_putstr_fd("0x", fd) == -1)
		return (-1);
	count = ft_put_ptr(ptr, 16, "0123456789abcdef", fd);
	if (count == -1)
		return (-1);
	return (count + 2);
}
