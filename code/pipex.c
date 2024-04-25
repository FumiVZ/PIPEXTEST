/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:23:42 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 14:47:42 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipe[i][0] || pipex->pipe[i][1])
	{
		close(pipex->pipe[i][0]);
		close(pipex->pipe[i][1]);
	}
	if (pipex->infile)
		close(pipex->infile);
	if (pipex->outfile)
		close(pipex->outfile);
}

static void	wait_execve(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	waitpid(pipex->pid, &status, 0);
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
	pipex->pipe_nmbs = count_pipes(pipex);
	pipex->pipe = malloc(sizeof(int *) * (pipex->pipe_nmbs + 1));
	while (i < pipex->pipe_nmbs)
	{
		pipex->pipe[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipe[i]) == -1)
		{
			close_pipes(pipex);
			malloc_failed(pipex);
		}
		i++;
	}
}

char	*find_path(char **env)
{
	if (!env)
		return (NULL);
	while (ft_strncmp("PATH", *env, 4))
		env++;
	if (!*env)
		return (NULL);
	return (*env + 5);
}

void print_tab(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		ft_printf_fd(2, "%s\n", tab[i]);
		i++;
	}
}

void	init_pipex(t_pipex *pipex, char **env)
{
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->i = 0;
	pipex->paths = ft_split(find_path(env), ':');
	if (!pipex->paths)
		pipex->paths = ft_split("/usr/local/bin:\
			/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.", ':');
	if (!pipex->paths)
		malloc_failed(pipex);
	crt_pipes(pipex);
	child_crt(*pipex, env);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	(void) ac;
	pipex.cmd = ft_split(av[1], ' ');
	init_pipex(&pipex, env);
	close_pipes(&pipex);
	wait_execve(&pipex);
	parent_free(&pipex);
	return (0);
}
