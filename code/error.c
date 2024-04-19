/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:51:11 by machrist          #+#    #+#             */
/*   Updated: 2024/04/19 13:22:03 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/error.h"

int	msg(char *err)
{
	ft_printf_fd(2, err);
	return (EXIT_FAILURE);
}

void	msg_error_cmd(char *err, t_pipex pipex)
{
	if (ft_strncmp(err, ERR_CMD, 10) == 0)
	{
		if (!pipex.cmd_args)
			ft_printf_fd(2, "%s", (char *)ERR_CMD_EMPTY);
		else if (!pipex.cmd_args[0])
			ft_printf_fd(2, "%s", (char *)ERR_CMD_EMPTY);
		else
			ft_printf_fd(2, err, pipex.cmd_args[0]);
	}
	else
	{
		if (!pipex.cmd_args)
			ft_printf_fd(2, "%s", (char *)ERR_ACCESS_EMPTY);
		else if (!pipex.cmd_args[0])
			ft_printf_fd(2, "%s", (char *)ERR_ACCESS_EMPTY);
		else
			ft_printf_fd(2, err, pipex.cmd_args[0]);
	}
}

void	msg_error_infile(char *err, t_pipex pipex)
{
	if (!pipex.infile_name)
		perror("pipex");
	else
		ft_printf_fd(2, err, pipex.infile_name, strerror(errno));
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	parent_free(&pipex);
	exit (EXIT_FAILURE);
}

void	msg_error_outfile(char *err, t_pipex pipex)
{
	if (!pipex.outfile_name)
		perror("pipex");
	else
		ft_printf_fd(2, err, pipex.outfile_name, strerror(errno));
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	parent_free(&pipex);
	exit (EXIT_FAILURE);
}

void	msg_error(char *err, t_pipex *pipex)
{
	perror(err);
	parent_free(pipex);
	exit (EXIT_FAILURE);
}
