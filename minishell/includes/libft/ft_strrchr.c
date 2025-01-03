/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:07:02 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/28 20:20:36 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*word;
	char	*loc;

	word = (char *)s;
	loc = NULL;
	if (c == '\0')
	{
		word += ft_strlen(word);
		return (word);
	}
	while (*word != '\0')
	{
		if ((unsigned char)*word == (unsigned char)c)
			loc = word;
		word++;
	}
	return (loc);
}
