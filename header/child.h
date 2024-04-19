/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:28:47 by machrist          #+#    #+#             */
/*   Updated: 2024/04/13 17:01:15 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "pipex.h"
# include "struct.h"
# include "error.h"
# include <libft.h>
# include <fcntl.h>

void	child_free(t_pipex *pipex);
int		msg(char *err);
void	msg_error_infile(char *err, t_pipex pipex);
void	msg_error_outfile(char *err, t_pipex pipex);
int		msg_error_cmd(char *err, t_pipex pipex);
void	msg_error(char *err, t_pipex *pipex);
void	parent_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);

#endif