/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:22 by machrist          #+#    #+#             */
/*   Updated: 2023/11/09 17:32:58 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cmp;

	cmp = (const unsigned char *)s;
	while (n-- > 0)
	{
		if (*cmp == (const unsigned char)c)
			return ((void *)cmp);
		cmp++;
	}
	return (NULL);
}
