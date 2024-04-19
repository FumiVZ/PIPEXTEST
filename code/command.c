/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/19 14:12:03 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	command_get(t_pipex *pipex)
{
	size_t	len;
	size_t	j;

	len = 0;
	while (pipex->cmd[pipex->i] && \
		(pipex->cmd[pipex->i][0] == '<' || pipex->cmd[pipex->i][0] == '>'))
		pipex->i += 2;
	while (pipex->cmd[pipex->i + len] && \
		!(pipex->cmd[pipex->i + len][0] == '<' || \
			pipex->cmd[pipex->i + len][0] == '>'))
		len++;
	pipex->cmd_args = malloc(sizeof(char *) * (len + 1));
	if (!pipex->cmd_args)
		msg_error(ERR_MALLOC, pipex);
	j = 0;
	while (j < len)
	{
		pipex->cmd_args[j] = pipex->cmd[pipex->i + j];
		j++;
	}
	pipex->cmd_args[j] = NULL;
}
