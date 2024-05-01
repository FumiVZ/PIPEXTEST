/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:20:40 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 01:21:57 by vincent          ###   ########.fr       */
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
	int				pipeid;
	int				*pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	pid_t	*pid;
	int		i;
	int		infile;
	char	*infile_name;
	int		outfile;
	char	*outfile_name;
	char	**paths;
	char	*cmd_paths;
	char	**cmd;
	int		cmd_nmbs;
	int		status;
	int		flag;
	int		nb_pipes;
	struct s_cmd	*cmds;
}	t_pipex;

void	print_tab(char **tab);
int		count_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex, t_cmd *cmd);
void	close_files(t_pipex	*pipex, t_cmd *cmd);
void	pipe_handle(t_pipex *pipex, t_cmd *cmd);
void	crt_pipes(t_pipex *pipex, t_cmd *cmd);

#endif