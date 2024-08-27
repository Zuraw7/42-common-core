/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:41:53 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/27 15:20:02 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*d = *s;
		d++;
		s++;
		i++;
	}
	return (dest);
}
/*
int main() {
    // Przykładowe dane do skopiowania
    char source[] = "Hello, World!";
    char destination[20];

    // Kopiowanie przy użyciu ft_memcpy
    ft_memcpy(destination, source, sizeof(source));

    // Wydrukowanie wyniku
    printf("Wynik ft_memcpy: %s\n", destination);

    // Resetowanie destination do celów porównania
    memset(destination, 0, sizeof(destination));

    // Kopiowanie przy użyciu memcpy
    memcpy(destination, source, sizeof(source));

    // Wydrukowanie wyniku
    printf("Wynik memcpy: %s\n", destination);

    return 0;
}*/
