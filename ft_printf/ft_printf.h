/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:17 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/14 18:27:03 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *text, ...);
int	ft_printf_format_specifier(va_list arg, char *text);
int	ft_printf_id(int x);
int	ft_printf_s(char *word_arg);
int	ft_printf_c(int c);
int	ft_printf_u(unsigned int x);
int	ft_printf_xx(unsigned int x, char text);
int	ft_printf_p(void *ptr);

#endif