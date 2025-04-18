/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:26:30 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/26 19:53:38 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdio.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p = (unsigned char)c;
		n--;
		p++;
	}
	return (s);
}
/*
int main ()
{
	  // Przykład 1: Inicjalizacja tablicy unsigned char
    unsigned char array1[5];
    ft_memset(array1, 42, sizeof(array1));

    // Przykład 2: Inicjalizacja bufora char
    char buffer[10];
    ft_memset(buffer, 'A', sizeof(buffer));

    // Wyświetlenie wyników
    printf("Przykład 1 - Tablica unsigned char:\n");
    for (size_t i = 0; i < sizeof(array1); ++i) {
        printf("%d ", array1[i]);
    }
    printf("\n");

    printf("Przykład 2 - Bufor char:\n");
    for (size_t i = 0; i < sizeof(buffer); ++i) {
        printf("%c ", buffer[i]);
    }
    printf("\n");
}*/
