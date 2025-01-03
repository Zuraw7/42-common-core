/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:40:30 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/14 08:58:51 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_s(char *word_arg)
{
	int		len;
	char	*word;

	if (!word_arg)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(word_arg);
	word = malloc(len + 1);
	if (!word)
		return (-1);
	ft_strlcpy(word, word_arg, len + 1);
	write(1, word, len);
	free(word);
	return (len);
}
