/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:06 by machrist          #+#    #+#             */
/*   Updated: 2024/04/29 18:51:25 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/child.h"

static char	*get_cmd(char **paths, char **cmd_args)
{
	char	*tmp;
	char	*command;

	if (!paths || !cmd_args)
		return (NULL);
	if (access(cmd_args[0], X_OK) == 0 || errno == EACCES)
		return (cmd_args[0]);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!command)
			return (NULL);
		if (access(command, X_OK) == 0 || errno == EACCES)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char	*get_cmd_with_path(t_pipex *pipex, t_cmd *cmds)
{
	if (!cmds->args)
		return (NULL);
	if (cmds->args[0][0] == '/' || !ft_strncmp(*cmds->args, "./", 2))
	{
		if (access(cmds->args[0], X_OK) == 0 || errno == EACCES)
			return (cmds->args[0]);
		ft_printf_fd(2, (char *)ERR_FILE, \
			cmds->args[0], strerror(errno));
		child_free(cmds);
		parent_free(pipex);
		exit (EXIT_FAILURE);
	}
	else
		return (get_cmd(pipex->paths, cmds->args));
}

static void	child_exec(t_pipex pipex, t_cmd cmds, char **env)
{
	redirect(&pipex, &cmds);
	close_files(&pipex, pipex.cmds);
	pipex.cmd_paths = get_cmd_with_path(&pipex, &cmds);
	if (!pipex.cmd_paths || errno == EACCES)
	{
		if (errno == EACCES)
			msg_error_cmd(ERR_ACCESS, cmds);
		else
			msg_error_cmd(ERR_CMD, cmds);
		child_free(&cmds);
		free_l(pipex.cmds);
		parent_free(&pipex);
		exit (EXIT_FAILURE);
	}
	execve(pipex.cmd_paths, cmds.args, env);
	free_l(pipex.cmds);
	parent_free(&pipex);
	child_free(&cmds);
	exit (EXIT_FAILURE);
}

void	single_command(t_pipex pipex, t_cmd *cmds, char **env)
{
	pipex.pid[0] = fork();
	if (pipex.pid[0] == -1)
		msg_error(ERR_FORK, &pipex);
	if (pipex.pid[0] == 0)
		child_exec(pipex, *cmds, env);
	close_files(&pipex, pipex.cmds);
	wait_execve(&pipex);
	free_l(pipex.cmds);
}

void	multiple_command(t_pipex pipex, t_cmd *cmds, char **env)
{
	int	i;

	i = 0;
	while (cmds)
	{
		pipe_handle(&pipex, cmds);
		pipex.pid[i] = fork();
		if (pipex.pid[i] == -1)
			msg_error(ERR_FORK, &pipex);
		if (pipex.pid[i] == 0)
			child_exec(pipex, *cmds, env);
		cmds = cmds->next;
		i++;
	}
	print_list(pipex.cmds);
	close_files(&pipex, pipex.cmds);
	free_l(pipex.cmds);
	wait_execve(&pipex);
	if (pipex.pid)
		free(pipex.pid);
}

void	child_crt(t_pipex pipex, char **env)
{
	t_cmd	*cmds;
	int		i;

	i = 0;
	pipex.status = -1;
	cmds = malloc(sizeof(t_cmd));
	while (pipex.cmd[pipex.i])
	{
		parse_cmd(&pipex, cmds);
		if (pipex.cmd[pipex.i] && chre(pipex.cmd[pipex.i], "&&") && pipex.status != 0)
			break ;
		if (pipex.cmd[pipex.i] && chre(pipex.cmd[pipex.i], "||") && pipex.status != 0)
			break ;
		pipex.cmds = cmds;
		if (cmds->next)
			multiple_command(pipex, cmds, env);
		else
			single_command(pipex, cmds, env);
		parent_free(&pipex);
	}
	close_files(&pipex, pipex.cmds);
}
