/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:20:40 by machrist          #+#    #+#             */
/*   Updated: 2024/04/19 13:28:01 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		i;
	int		infile;
	char	*infile_name;
	int		outfile;
	char	*outfile_name;
	char	**paths;
	char	*cmd_paths;
	char	**cmd_args;
	char	**cmd;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		pipe[2];
	int		p_i;

}	t_pipex;

void	print_tab(char **tab);

#endif