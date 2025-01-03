/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_src_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:35:32 by rkobelie          #+#    #+#             */
/*   Updated: 2024/12/16 09:10:06 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// czasowo src funkcje bedą tu, jak zadziała exec zrobie porządek

char	*ft_strtok(char *str, char delim) // dziele path na "tokeny"
{
	static char	*static_str;
	char		*token;

	if (str)
		static_str = str;
	if (!static_str)
		return (NULL);
	token = static_str;
	while (*static_str && *static_str != delim)
		static_str++;
	if (*static_str == delim)
	{
		*static_str = '\0';
		static_str++;
	}
	else
		static_str = NULL;
	if (*token)
		return (token);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*copy;

	i = 0;
	len = ft_strlen(s);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
