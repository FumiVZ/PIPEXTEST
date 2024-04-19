/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:00:24 by machrist          #+#    #+#             */
/*   Updated: 2023/11/07 16:51:20 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	char		*s;

	s = (char *)src;
	d = (char *)dest;
	if (s == d || n == 0)
		return (dest);
	i = 0;
	if (s < d)
		while (n--)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			++i;
		}
	}
	return (dest);
}
