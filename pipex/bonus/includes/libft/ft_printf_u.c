/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:07:44 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/13 21:07:56 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	s_intlen(unsigned int n)
{
	unsigned int	len;

	if (n == 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	s_putnbr_fd(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((n % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((n + '0'), fd);
}

int	ft_printf_u(unsigned int x)
{
	unsigned int	len;

	len = s_intlen(x);
	s_putnbr_fd(x, 1);
	return (len);
}
