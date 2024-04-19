/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:54:06 by machrist          #+#    #+#             */
/*   Updated: 2024/02/13 14:57:26 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_nmbs)
		close(pipex->pipe[i++]);
	if (pipex->id == 0)
		close(pipex->infile);
	if (pipex->id == pipex->cmd_nmbs - 1)
		close(pipex->outfile);
}

static void	wait_execve(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs)
	{
		waitpid(pipex->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		parent_free(pipex);
		exit (WEXITSTATUS(status));
	}
}

static void	crt_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->pipe)
		msg_error(ERR_PIPE, pipex);
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
			msg_error(ERR_PIPE, pipex);
		i++;
	}
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->paths = find_path(env);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	pipex->cmd_paths_default = ft_split("/usr/local/bin:\
		/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.", ':');
	pipex->cmd_nmbs = ac - 3;
	pipex->pipe = NULL;
	pipex->pid = malloc(sizeof(pid_t) * pipex->cmd_nmbs);
	if (!pipex->pid)
		malloc_failed(pipex);
	pipex->pipe_nmbs = 2 * (pipex->cmd_nmbs - 1);
	pipex->pipe = malloc(sizeof(int) * pipex->pipe_nmbs);
	if (!pipex->pipe)
		malloc_failed(pipex);
	pipex->all_cmds = av + 2;
	crt_pipes(pipex);
	pipex->id = -1;
	while (++(pipex->id) < pipex->cmd_nmbs)
		child_crt(*pipex, env, ac, av);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
		return (msg(ERR_INPUT));
	init_pipex(&pipex, ac, av, env);
	close_pipes(&pipex);
	wait_execve(&pipex);
	parent_free(&pipex);
	return (0);
}
