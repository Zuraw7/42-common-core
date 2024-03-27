/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:01:11 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/24 17:30:59 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*firstc;

	firstc = (char *)s;
	if (c == '\0')
	{
		firstc += ft_strlen(firstc);
		return (firstc);
	}
	while (*firstc != '\0')
	{
		if ((unsigned char)*firstc == (unsigned char)c)
			return (firstc);
		firstc++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while ((i < size - 1) && (src[i] != '\0'))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = malloc(lens1 + lens2 + 1);
	if (str == NULL)
		return (NULL);
	if (lens1 > 0)
		ft_strlcpy(str, s1, lens1 + 1);
	if (lens2 > 0)
		ft_strlcpy(str + lens1, s2, lens2 + 1);
	str[lens1 + lens2] = '\0';
	return (str);
}

char	*join_and_free(char **read_text, char *temp)
{
	char	*recreated;

	recreated = ft_strjoin(*read_text, temp);
	free(*read_text);
	free(temp);
	return (recreated);
}
