/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:09:39 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/14 18:53:04 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_intlen(unsigned long long n)
{
	int	len;

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

static void	s_swap(char *s)
{
	int		i;
	int		j;
	int		len;
	char	temp;

	len = ft_strlen(s);
	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
}

static void	s_convert(char *numb, unsigned long long x)
{
	char	*hextab;
	int		i;

	hextab = "abcdef";
	i = 0;
	while (x != 0)
	{
		if (x % 16 >= 10)
			numb[i] = hextab[(x % 16) % 10];
		else
			numb[i] = (x % 16) + '0';
		x /= 16;
		i++;
	}
	numb[i] = '\0';
}

int	ft_printf_p(void *ptr)
{
	unsigned long long	address;
	int					len;
	char				*numb;

	if (ptr == NULL)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	address = (unsigned long long)ptr;
	len = s_intlen(address);
	numb = malloc(len + 1 * sizeof(char));
	if (!numb)
		return (-1);
	s_convert(numb, address);
	s_swap(numb);
	write(1, "0x", 2);
	write(1, numb, ft_strlen(numb));
	len = ft_strlen(numb) + 2;
	free(numb);
	return (len);
}
