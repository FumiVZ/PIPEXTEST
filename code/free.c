/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:53:23 by machrist          #+#    #+#             */
/*   Updated: 2024/04/30 16:04:31 by vzuccare         ###   ########lyon.fr   */
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
	if (pipex->cmd && pipex->cmd[0] && pipex->cmd[0][0])
		free_split(pipex->cmd, tablen(pipex->cmd));
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
