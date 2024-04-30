/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:23:42 by machrist          #+#    #+#             */
/*   Updated: 2024/04/30 14:56:44 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

void	close_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->pipe)
		return ;
	while (i < 2 * (pipex->cmd_nmbs - 1))
		close(cmd->pipe[i++]);
}

void	wait_execve(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < pipex->cmd_nmbs)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			pipex->status = WEXITSTATUS(status);
		}
		i++;
	}
	if (WIFEXITED(status))
	{
		pipex->status = WEXITSTATUS(status);
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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
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
	pipex->flag = 0;
	if (!pipex->paths)
		pipex->paths = ft_split("/usr/local/bin:\
			/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.", ':');
	if (!pipex->paths)
		malloc_failed(pipex);
	child_crt(*pipex, env);
	parent_free(pipex);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	(void) ac;
	if (ac != 2)
	{
		ft_printf_fd(2, "DEBILE");
		return (1);
	}
	pipex.cmd = ft_split(av[1], ' ');
	init_pipex(&pipex, env);
	return (0);
}
