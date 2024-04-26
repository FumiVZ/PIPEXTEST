/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:20:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/26 02:15:04 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	list_init(t_cmd *head)
{
	head->args = NULL;
	head->infiles = NULL;
	head->infiles_name = NULL;
	head->outfiles = NULL;
	head->outfiles_name = NULL;
	head->next = NULL;
}

void	print_list(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;
	int		len;
	
	len = 0;
	tmp = head;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			printf("args %d: %s\n", i, tmp->args[i]);
			i++;
		}
		i = 0;
		while (tmp->infiles_name[i])
		{
			printf("infile %d: %s\n", i, tmp->infiles_name[i]);
			i++;
		}
		i = 0;
		while (tmp->outfiles_name[i])
		{
			printf("outfile %d: %s\n", i, tmp->outfiles_name[i]);
			i++;
		}
		printf("\n");
		len++;
		printf("len: %d\n", len);
		tmp = tmp->next;
	}
	printf("len: %d\n", len);
}