/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:09:11 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/29 16:18:32 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n && (str1 || str2))
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		n--;
	}
	return (0);
}
