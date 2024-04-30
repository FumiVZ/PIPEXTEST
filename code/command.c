/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:46:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/30 14:25:52 by vzuccare         ###   ########lyon.fr   */
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
	while (cmd)
	{
		if (cmd->infiles)
		{
			while (cmd->infiles[i] != -1)
			{
				close(cmd->infiles[i]);
				i++;
			}
		}
		i = 0;
		if (cmd->outfiles)
		{
			while (cmd->outfiles[i] != -1)
			{
				close(cmd->outfiles[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}

void	crt_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (pipex->cmd_nmbs < 2)
		return ;
	ft_printf_fd(2, "%d\n", pipex->cmd_nmbs);
	cmd->pipe = malloc(sizeof(int) * 2 * (pipex->cmd_nmbs - 1));
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
	if (pipex->cmd_nmbs < 2)
		return ;
	if (!pipex->cmds->pipe)
		ft_printf_fd(2, "pipe is NULL\n");
	if (cmd->pipeid == 0)
	{
		ft_printf_fd(2, "pipe start\n");
		dup2(pipex->cmds->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[1]);
		close(cmd->pipe[0]);
		ft_printf_fd(2, "STDOUT %d\n", 1);
	}
	else if (cmd->pipeid == pipex->cmd_nmbs - 1)
	{
		ft_printf_fd(2, "pipe end\n");
		ft_printf_fd(2, "pipeid %d\n", cmd->pipeid);
		dup2(pipex->cmds->pipe[2 * cmd->pipeid - 2], STDIN_FILENO);
		close(pipex->cmds->pipe[2 * cmd->pipeid - 2]);
		close(pipex->cmds->pipe[2 * cmd->pipeid - 1]);
		ft_printf_fd(2, "END STDIN %d\n", 2 * cmd->pipeid - 2);
	}
	else
	{
		ft_printf_fd(2, "pipe middle\n");
		dup2(pipex->cmds->pipe[2 * cmd->pipeid - 2], STDIN_FILENO);
		dup2(pipex->cmds->pipe[2 * cmd->pipeid + 1], STDOUT_FILENO);
		close(pipex->cmds->pipe[2 * cmd->pipeid - 2]);
		close(pipex->cmds->pipe[2 * cmd->pipeid + 1]);
	}
}

void	redirect(t_pipex *pipex, t_cmd *cmd)
{
	int		i;

	i = 0;
	(void)pipex;
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

