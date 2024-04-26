/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:20:40 by machrist          #+#    #+#             */
/*   Updated: 2024/04/25 22:11:09 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/wait.h>

typedef struct s_cmd
{
	char			**args;
	int				*infiles;
	char			**infiles_name;
	int				*outfiles;
	char			**outfiles_name;
	struct s_cmd	*next;
}	t_cmd;

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
	char	**cmd;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		**pipe;
	int		p_i;
}	t_pipex;

void	print_tab(char **tab);
int		count_pipes(t_pipex *pipex);

#endif