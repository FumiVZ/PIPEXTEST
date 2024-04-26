/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/27 00:51:10 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

//reproduce the behavior of pipe in bash, we need to write the output of 
//previous command to the input of the next command
//the number of pipe is equal to the number of node in the linked list

void	close_files(t_pipex	*pipex, t_cmd *cmd)
{
	int	i;
	
	(void)pipex;
	i = 0;
	if (cmd->infiles)
	{
		while (cmd->infiles[i] != -1)
			close(cmd->infiles[i++]);
		free(cmd->infiles);
	}
	i = 0;
	if (cmd->outfiles)
	{
		while (cmd->outfiles[i] != -1)
			close(cmd->outfiles[i++]);
		free(cmd->outfiles);
	}
}

void	crt_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (pipex->cmd_nmbs < 2)
		return ;
	cmd->pipe = malloc(sizeof(int) * pipex->nb_pipes);
	if (!cmd->pipe)
		msg_error(ERR_PIPE, pipex);
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(cmd->pipe + 2 * i) == -1)
			msg_error(ERR_PIPE, pipex);
		i++;
	}
}

void	pipe_handle(t_pipex *pipex, t_cmd *cmd)
{
	crt_pipes(pipex, cmd);
	if (pipex->cmd_nmbs < 2)
		return ;
	if (cmd->next && cmd->pipeid == 0)
	{
		ft_printf_fd(2, "pipe start\n");
		dup2(cmd->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[1]);
	}
	if (cmd->pipeid == -1)
	{
		ft_printf_fd(2, "pipe end\n");
		dup2(cmd->pipe[2 * pipex->cmd_nmbs - 2], STDIN_FILENO);
		close(cmd->pipe[2 * pipex->cmd_nmbs - 2]);
	}
	else if (cmd->pipeid > 0 && cmd->next)
	{
		ft_printf_fd(2, "pipe middle\n");
		dup2(cmd->pipe[2 * cmd->pipeid + 1], STDOUT_FILENO);
		close(cmd->pipe[2 * cmd->pipeid + 1]);
		dup2(cmd->pipe[2 * cmd->pipeid - 2], STDIN_FILENO);
		close(cmd->pipe[2 * cmd->pipeid - 2]);
	}
}

void	redirect(t_pipex *pipex, t_cmd *cmd)
{
	int		i;

	i = 0;
	pipe_handle(pipex, cmd);
	if (cmd->infiles)
	{
		while (cmd->infiles[i] != -1)
			i++;
		dup2(cmd->infiles[i - 1], STDIN_FILENO);
		close(cmd->infiles[i - 1]);
	}
	if (cmd->outfiles)
	{
		i = 0;
		while (cmd->outfiles[i] != - 1)
			i++;
		dup2(cmd->outfiles[i - 1], STDOUT_FILENO);
		close(cmd->outfiles[i - 1]);
	}
}

