/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:07:04 by machrist          #+#    #+#             */
/*   Updated: 2023/11/10 17:11:46 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_ferrorclr(t_list *lst, void *tmp, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	free(tmp);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*tmp;
	t_list	*begin;

	if (lst)
	{
		tmp = f(lst->content);
		begin = ft_lstnew(tmp);
		if (!begin)
			return (ft_ferrorclr(begin, tmp, del));
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst->content);
			new = ft_lstnew(tmp);
			if (!new)
				return (ft_ferrorclr(begin, tmp, del));
			ft_lstadd_back(&begin, new);
			lst = lst->next;
		}
		return (begin);
	}
	return (NULL);
}
