/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:20:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/25 18:31:19 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	print_list(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			ft_printf_fd(2, "%s ", tmp->args[i]);
			i++;
		}
		ft_printf_fd(2, "\n");
		tmp = tmp->next;
	}
}

int	insert_back(t_cmd **head, t_pipex *pipex)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (-1);
	new->args = command_get(pipex);
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}