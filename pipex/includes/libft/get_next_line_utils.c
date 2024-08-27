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

#include "libft.h"

char	*join_and_free(char **read_text, char *temp)
{
	char	*recreated;

	recreated = ft_strjoin(*read_text, temp);
	free(*read_text);
	free(temp);
	return (recreated);
}
