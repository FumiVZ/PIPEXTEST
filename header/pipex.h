/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:18:11 by machrist          #+#    #+#             */
/*   Updated: 2024/04/13 16:58:19 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include "struct.h"
# include "error_msg.h"
# include <fcntl.h>
# include <errno.h>

void	command_get(t_pipex *pipex);
void	msg_error(char *err, t_pipex *pipex);
int		msg(char *err);
void	msg_error_infile(char *err, t_pipex pipex);
void	msg_error_outfile(char *err, t_pipex pipex);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
void	child_crt(t_pipex pipex, char **env);
char	*find_path(char **env);
void	malloc_failed(t_pipex *pipex);
int		flags(char *str);

#endif