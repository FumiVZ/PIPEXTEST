/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:23:40 by machrist          #+#    #+#             */
/*   Updated: 2024/02/10 14:22:30 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# define ERR_FILE "pipex: %s: %s\n"
# define ERR_INPUT "Invalid number of arguments."
# define ERR_PIPE "pipe failed"
# define ERR_CMD "pipex: %s: command not found\n"
# define ERR_CMD_EMPTY "pipex: command not found\n"
# define ERR_FORK "fork failed"
# define ERR_MALLOC "malloc failed"
# define ERR_ACCESS "pipex: %s: permission denied\n"
# define ERR_ACCESS_EMPTY "pipex: permission denied\n"

#endif