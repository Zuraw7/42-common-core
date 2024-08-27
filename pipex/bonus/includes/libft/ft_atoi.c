/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:32:56 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/29 20:32:27 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_atoi(const char *nptr)
{
	char	*snum;
	int		num;
	int		sign;

	sign = 1;
	snum = (char *)nptr;
	num = 0;
	while (*snum == '\t' || *snum == '\n' || *snum == '\r'
		|| *snum == '\v' || *snum == '\f' || *snum == ' ')
		snum++;
	if (*snum == '-' || *snum == '+')
	{
		if (*snum == '-')
			sign *= -1;
		else
			sign = 1;
		snum++;
	}
	while (*snum >= '0' && *snum <= '9')
	{
		num = num * 10 + (*snum - '0');
		snum++;
	}
	return (num * sign);
}
