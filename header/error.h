/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:51:45 by machrist          #+#    #+#             */
/*   Updated: 2024/02/13 14:52:26 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "struct.h"
# include <libft.h>
# include "error_msg.h"
# include <stdio.h>
# include <errno.h>

void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);

#endif