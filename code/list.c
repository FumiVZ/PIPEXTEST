/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:20:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/30 16:15:42 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_l(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	while (head)
	{
		i = -1;
		if (head->args)
		{
			while (head->args[++i])
				free(head->args[i]);
			free(head->args);
		}
		i = 0;
		if (head->infiles_name)
		{
			while (head->infiles_name[i])
			{
				free(head->infiles_name[i]);
				i++;
			}
			free(head->infiles_name);
			free(head->infiles);
		}
		i = 0;
		if (head->outfiles_name)
		{
			while (head->outfiles_name[i])
			{
				free(head->outfiles_name[i]);
				i++;
			}
			free(head->outfiles_name);
			free(head->outfiles);
		}
		if (head->pipe)
			free(head->pipe);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	list_init(t_cmd *head)
{
	head->args = NULL;
	head->infiles = NULL;
	head->infiles_name = NULL;
	head->outfiles = NULL;
	head->outfiles_name = NULL;
	head->next = NULL;
	head->pipe = NULL;
	head->pipeid = 0;
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
		if (tmp->args)
		{
			while (tmp->args[i])
			{
				printf("args %d: %s\n", i, tmp->args[i]);
				i++;
			}
		}
		i = 0;
		if (tmp->infiles_name)
		{
			while (tmp->infiles_name[i])
			{
				printf("infile %d: %s\n", i, tmp->infiles_name[i]);
				i++;
			}
		}
		i = 0;
		if (tmp->outfiles_name)
		{
			while (tmp->outfiles_name[i])
			{
				printf("outfile %d: %s\n", i, tmp->outfiles_name[i]);
				i++;
			}
		}
		printf("pipeid: %d\n", tmp->pipeid);
		printf("\n");
		len++;
		printf("len: %d\n", len);
		tmp = tmp->next;
	}
}
