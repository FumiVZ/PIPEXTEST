/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:13:22 by machrist          #+#    #+#             */
/*   Updated: 2023/11/08 20:35:11 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0 && n > -2147483648)
	{
		n = -n;
		len++;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	size_t	len;
	size_t	i;
	char	*str;

	nb = n;
	len = ft_itoa_len(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 1;
	if (n < 0)
		nb = -nb;
	if (nb == 0)
		str[nb] = '0';
	while (nb >= 1)
	{
		str[len - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (n < 0)
		*str = '-';
	str[len] = '\0';
	return (str);
}
