/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:32:56 by pzurawic          #+#    #+#             */
/*   Updated: 2025/04/17 13:10:55 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long	ft_atoi(const char *nptr)
{
	char	*snum;
	long	num;
	long	sign;

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
