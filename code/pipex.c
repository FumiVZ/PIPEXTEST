/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:23:42 by machrist          #+#    #+#             */
/*   Updated: 2024/04/29 10:15:26 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

void	close_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < pipex->nb_pipes)
		close(cmd->pipe[i++]);
}

void	wait_execve(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	printf("STATUS: %d\n", status);
	while (i < pipex->cmd_nmbs - 1)
	{
		waitpid(pipex->pid[i], &status, 0);
		i++;
	}
	free(pipex->pid);
	pipex->status = status;
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
	while (pipex->cmd[pipex->i])
	{
		if (chre(pipex->cmd[pipex->i], "&&") && pipex->status == 0)
			child_crt(*pipex, env);
		else if (!chre(pipex->cmd[pipex->i], "||") || pipex->status != 0)
			child_crt(*pipex, env);
		pipex->i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int	i;

	i = 0;
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
