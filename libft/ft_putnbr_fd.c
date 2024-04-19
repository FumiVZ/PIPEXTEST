/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:00:22 by machrist          #+#    #+#             */
/*   Updated: 2024/01/16 13:53:51 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(int n, int len_base, char *base, int fd)
{
	int		count;
	int		tmp;
	char	buffer[128];
	int		s;

	count = 0;
	s = 0;
	if (n < 0)
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
	if (n < 0 && s++ == 0)
		n = -n;
	if (n == 0)
		buffer[count++] = '0';
	while (n != 0)
	{
		buffer[count++] = base[n % len_base];
		n = n / len_base;
	}
	tmp = count;
	while (--tmp >= 0)
		if (ft_putchar_fd(buffer[tmp], fd) == -1)
			return (-1);
	return (count + s);
}
