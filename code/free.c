/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:53:23 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 01:37:40 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/child.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	if (pipex->paths)
	{
		i = 0;
		while (pipex->paths[i])
			free(pipex->paths[i++]);
		free(pipex->paths);
	}
	pipex->cmd = NULL;
}

void	child_free(t_pipex *pipex)
{
	if (pipex->cmd)
		free_split(pipex->cmd, tablen(pipex->cmd));
	if (pipex->pid)
		free(pipex->pid);
	close(0);
	close(1);
}


void	malloc_failed(t_pipex *pipex)
{
	ft_printf_fd(2, "pipex: malloc failed\n");
	parent_free(pipex);
	exit (EXIT_FAILURE);
}
