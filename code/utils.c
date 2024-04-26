/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:27:22 by vzuccare          #+#    #+#             */
/*   Updated: 2024/04/26 11:08:58 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	flags(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (001 | 0100);
		return (001 | 0100 | 01000);
	}
	return (0);
}

int	count_pipes(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->cmd[j])
	{
		if (ft_strncmp(pipex->cmd[j], "|", 1) == 0)
			i++;
		if (ft_strncmp(pipex->cmd[j], ">", 1) == 0)
			i++;
		if (ft_strncmp(pipex->cmd[j], ">>", 2) == 0)
			i++;
		if (ft_strncmp(pipex->cmd[j], "<", 1) == 0)
			i++;
		j++;
	}
	return (i);
}
