/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:45:21 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/03 14:45:24 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapped;
	unsigned int	i;
	unsigned int	len;

	if (s == NULL || !f)
		return (NULL);
	len = ft_strlen(s);
	mapped = malloc(len + 1);
	if (mapped == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		mapped[i] = f(i, (char)s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
