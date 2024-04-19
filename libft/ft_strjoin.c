/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:14:52 by machrist          #+#    #+#             */
/*   Updated: 2024/01/18 17:57:06 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	str_len;

	if (!s1 || !s2)
		return (NULL);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * str_len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, str_len);
	ft_strlcat(str, s2, str_len);
	return (str);
}
