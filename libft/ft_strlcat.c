/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:11:40 by machrist          #+#    #+#             */
/*   Updated: 2023/11/07 18:24:31 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = 0;
	s_len = 0;
	i = 0;
	while (dst[d_len] && d_len < size)
		d_len++;
	while (src[s_len])
		s_len++;
	while (src[i] && d_len + i + 1 < size)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	if (d_len < size)
		dst[d_len + i] = '\0';
	return (d_len + s_len);
}
