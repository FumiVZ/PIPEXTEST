/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:47 by machrist          #+#    #+#             */
/*   Updated: 2024/04/27 00:21:49 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "pipex.h"
# include "struct.h"
# include "error.h"
# include <libft.h>
# include <fcntl.h>

void	child_free(t_cmd *cmds);
int		msg(char *err);
void	msg_error_infile(char *err, t_pipex pipex);
void	msg_error_outfile(char *err, t_pipex pipex);
int		msg_error_cmd(char *err, t_cmd cmds);
void	msg_error(char *err, t_pipex *pipex);
void	parent_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex, t_cmd *cmd);
void	sub_dup2(int read, int write);
void	parse_cmd(t_pipex *pipex, t_cmd *cmds);

#endif