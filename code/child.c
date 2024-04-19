/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:06 by machrist          #+#    #+#             */
/*   Updated: 2024/04/19 14:35:37 by vzuccare         ###   ########lyon.fr   */
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

static char	*get_cmd_with_path(t_pipex *pipex)
{
	if (!pipex->cmd_args)
		return (NULL);
	if (pipex->cmd_args[0][0] == '/' || !ft_strncmp(*pipex->cmd_args, "./", 2))
	{
	ft_printf_fd(2, "cmd_args: %s\n", pipex->cmd_args[0]);
		if (access(pipex->cmd_args[0], X_OK) == 0 || errno == EACCES)
			return (pipex->cmd_args[0]);
		ft_printf_fd(2, (char *)ERR_FILE, \
			pipex->cmd_args[0], strerror(errno));
		child_free(pipex);
		parent_free(pipex);
/* 		if (pipex->i == ac - 1)
			exit (127); */
		exit (EXIT_FAILURE);
	}
	else
		return (get_cmd(pipex->paths, pipex->cmd_args));
}

static void	sub_dup2(int read, int write)
{
	dup2(read, 0);
	dup2(write, 1);
}

static void	child_exec(t_pipex pipex, char **env)
{
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		pipex.cmd_paths = get_cmd_with_path(&pipex);
		if (!pipex.cmd[pipex.i])
			pipex.cmd_paths = get_cmd(pipex.paths, pipex.cmd_args);
		if (!pipex.cmd || errno == EACCES)
		{
			if (errno == EACCES)
				msg_error_cmd(ERR_ACCESS, pipex);
			else
				msg_error_cmd(ERR_CMD, pipex);
			child_free(&pipex);
			parent_free(&pipex);
		/* 		if (pipex.id == pipex.cmd_nmbs - 1)
			exit (127); */
			exit (EXIT_FAILURE);
		}
		ft_printf_fd(2, "cmd_paths: %s\n", pipex.cmd_paths);
		print_tab(pipex.cmd_args);
		execve(pipex.cmd_paths, pipex.cmd_args, env);
		child_free(&pipex);
		parent_free(&pipex);
		exit (EXIT_FAILURE);
	}
}

void	child_crt(t_pipex pipex, char **env)
{
	while (pipex.cmd[pipex.i])
	{
		if (pipex.cmd[pipex.i][0] == '<')
		{
			pipex.infile_name = pipex.cmd[pipex.i + 1];
			pipex.infile = open(pipex.cmd[pipex.i + 1], O_RDONLY);
			if (pipex.infile < 0)
				msg_error_infile(ERR_FILE, pipex);
			sub_dup2(pipex.infile, pipex.pipe[1]);
		}
		else if (pipex.cmd[pipex.i][0] == '>')
		{
			pipex.outfile_name = pipex.cmd[pipex.i + 1];
			pipex.outfile = open(pipex.cmd[pipex.i + 1], \
				flags(pipex.cmd[pipex.i + 1]), 0644);
			if (pipex.outfile < 0)
				msg_error_outfile(ERR_FILE, pipex);
			sub_dup2(pipex.pipe[0], pipex.outfile);
		}
		else if (pipex.cmd[pipex.i][0] == '|')
			sub_dup2(pipex.pipe[0], pipex.pipe[1]);
		else
		{
			command_get(&pipex);
			printf("ft_strstrlen: %zu\n", ft_strstrlen(pipex.cmd_args));
			printf("i: %d\n", pipex.i);
			pipex.i++;
			break ;
		}
		pipex.i++;
	}
	close_pipes(&pipex);
	child_exec(pipex, env);
}
