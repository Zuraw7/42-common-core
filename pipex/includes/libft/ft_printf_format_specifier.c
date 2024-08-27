/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_specifier.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:39:44 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/13 23:32:04 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_format_specifier(va_list args, char *text)
{
	int	len;

	len = 0;
	if (*text == 'i' || *text == 'd')
		len += ft_printf_id(va_arg(args, int));
	else if (*text == 's')
		len += ft_printf_s(va_arg(args, char *));
	else if (*text == 'c')
		len += ft_printf_c(va_arg(args, int));
	else if (*text == 'u')
		len += ft_printf_u(va_arg(args, unsigned int));
	else if (*text == '%')
		len += write(1, "%", 1);
	else if (*text == 'x' || *text == 'X')
		len += ft_printf_xx(va_arg(args, unsigned int), *text);
	else if (*text == 'p')
		len += ft_printf_p(va_arg(args, void *));
	return (len);
}
