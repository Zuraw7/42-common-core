/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:56:51 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/27 15:27:07 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	word_length(char const *s, char c)
{
	int	length;

	length = 0;
	while (*s && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

static	void	s_free(char **result)
{
	while (*result)
	{
		free(*result);
		result--;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	int		num_words;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	num_words = count_words(s, c);
	result = malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < num_words)
	{
		while (*s == c)
			s++;
		result[i] = ft_substr(s, 0, word_length(s, c));
		if (!result[i])
		{
			s_free(result);
			return (NULL);
		}
		s += word_length(s, c);
	}
	result[i] = NULL;
	return (result);
}
