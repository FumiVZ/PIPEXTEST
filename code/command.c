/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/26 17:46:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

//reproduce the behavior of pipe in bash, we need to write the output of 
//previous command to the input of the next command
//the number of pipe is equal to the number of node in the linked list

void	pipe_handle(t_pipex *pipex, t_cmd *cmd)
{

}

void	redirect(t_pipex *pipex, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->infiles)
	{
		while (cmd->infiles[i])
			i++;
		dup2(cmd->infiles[i], STDIN_FILENO);
		close(cmd->infiles[i]);
	}
	if (cmd->outfiles)
	{
		i = 0;
		while (cmd->outfiles[i])
			i++;
		dup2(cmd->outfiles[i], STDOUT_FILENO);
		close(cmd->outfiles[i]);
	}
	pipe_handle(pipex, cmd);
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
