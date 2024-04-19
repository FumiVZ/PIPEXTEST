/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:51:47 by machrist          #+#    #+#             */
/*   Updated: 2024/01/16 14:21:51 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_putendl_fd(char *s, int fd)
{
	int	tmp;
	int	res;

	tmp = ft_putstr_fd(s, fd);
	if (tmp == -1)
		return (-1);
	res = tmp;
	tmp = ft_putchar_fd('\n', fd);
	if (tmp == -1)
		return (-1);
	res += tmp;
	return (res);
}
