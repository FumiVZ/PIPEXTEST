/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/25 21:01:25 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	redir_dup(t_pipex *pipex)
{
	if (pipex->cmd[pipex->i][0] == '<')
	{
		pipex->infile_name = pipex->cmd[pipex->i + 1];
		pipex->infile = open(pipex->cmd[pipex->i + 1], O_RDONLY);
		if (pipex->infile < 0)
			msg_error_infile(ERR_FILE, *pipex);
		sub_dup2(pipex->infile, pipex->pipe[pipex->p_i][1]);
		pipex->p_i++;
		return (1);
	}
	else if (pipex->cmd[pipex->i][0] == '>')
	{
		pipex->outfile_name = pipex->cmd[pipex->i + 1];
		pipex->outfile = open(pipex->cmd[pipex->i + 1], \
			flags(pipex->cmd[pipex->i + 1]), 0644);
		if (pipex->outfile < 0)
			msg_error_outfile(ERR_FILE, *pipex);
		sub_dup2(pipex->pipe[pipex->p_i][0], pipex->outfile);
		pipex->p_i++;
		return (1);
	}
	return (0);
}

char	**command_get(t_pipex *pipex)
{
	size_t	len;
	size_t	j;
	char	**str;

	len = 0;
	while (pipex->cmd[pipex->i] && \
		(pipex->cmd[pipex->i][0] == '<' || pipex->cmd[pipex->i][0] == '>'))
		pipex->i += 2;
	while (pipex->cmd[pipex->i + len] && \
		!(pipex->cmd[pipex->i + len][0] == '<' || \
			pipex->cmd[pipex->i + len][0] == '>' || \
				pipex->cmd[pipex->i + len][0] == '|'))
		len++;
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		msg_error(ERR_MALLOC, pipex);
	j = 0;
	while (j < len)
	{
		str[j] = pipex->cmd[pipex->i + j];
		j++;
	}
	str[j] = NULL;
	return (str);
}
