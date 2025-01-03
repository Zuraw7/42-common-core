/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:06:25 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/14 17:24:39 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_intlen(unsigned int n)
{
	int	len;

	if (n <= 0)
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

static void	s_build(char *numb, unsigned int x)
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

static void	s_toupper(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
}

int	ft_printf_xx(unsigned int x, char text)
{
	int		len;
	char	*numb;

	if (x == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	len = s_intlen(x);
	numb = malloc(len + 1 * sizeof(char));
	if (!numb)
		return (-1);
	s_build(numb, x);
	s_swap(numb);
	if (text == 'X')
		s_toupper(numb);
	len = ft_strlen(numb);
	write(1, numb, len);
	free(numb);
	return (len);
}
