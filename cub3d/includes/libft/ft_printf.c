/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:38:05 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/14 18:58:54 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *text, ...)
{
	va_list	args;
	int		len;

	va_start(args, text);
	len = 0;
	while (*text != '\0')
	{
		if (*text == '%')
		{
			text++;
			len += ft_printf_format_specifier(args, (char *)text);
		}
		else
		{
			write(1, text, 1);
			len++;
		}
		text++;
	}
	va_end (args);
	return (len);
}
