/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:04:35 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/28 19:27:11 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size <= destlen)
		return (srclen + size);
	i = 0;
	if (size > 0)
	{
		while ((i < size - destlen - 1) && src[i] != '\0')
		{
			dest[destlen + i] = src[i];
			i++;
		}
	}
	dest[destlen + i] = '\0';
	return (srclen + destlen);
}
