/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:18:11 by machrist          #+#    #+#             */
/*   Updated: 2024/05/01 01:22:47 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include "struct.h"
# include "error_msg.h"
# include "child.h"
# include <fcntl.h>
# include <errno.h>

char	**command_get(t_pipex *pipex);
void	msg_error(char *err, t_pipex *pipex);
int		msg(char *err);
void	msg_error_infile(char *err, t_pipex pipex);
void	msg_error_outfile(char *err, t_pipex pipex);
void	parent_free(t_pipex *pipex);
int		child_crt(t_pipex pipex, char **env);
char	*find_path(char **env);
void	malloc_failed(t_pipex *pipex);
int		flags(char *str);
void	print_list(t_cmd *head);
void	list_init(t_cmd *head);
void	free_l(t_cmd *head);
int		chre(char *s1, char *s2);
void	redirect(t_pipex *pipex, t_cmd *cmd);
void	close_pipes(t_pipex *pipex, t_cmd *cmd);
int		wait_execve(t_pipex *pipex);

#endif