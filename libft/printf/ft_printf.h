/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:06:25 by machrist          #+#    #+#             */
/*   Updated: 2024/01/16 13:55:07 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf_fd(int fd, const char *format, ...);
int		ft_test_ptr(unsigned long long n, int fd);
int		ft_putchar_fd(char c, int fd);
long	ft_putstr_fd(char *s, int fd);
int		ft_putnbr_base_fd(int n, int len_base, char *base, int fd);

#endif