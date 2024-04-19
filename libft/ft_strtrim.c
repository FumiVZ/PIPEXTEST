/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:17:37 by machrist          #+#    #+#             */
/*   Updated: 2023/11/08 19:09:51 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_check(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && ft_in_check(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end + 1 > 0 && ft_in_check(s1[end], set))
		end--;
	return (ft_substr(s1, (unsigned int)start, end - start + 1));
}
