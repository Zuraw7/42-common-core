/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:11:23 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/22 20:14:43 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_operators(char *operators)
{
	operators[0] = '&';
	operators[1] = '|';
	operators[2] = '>';
	operators[3] = '<';
}

// Sprawdza czy dany fragment tekstu jest operatorem
bool	look_for_operator(char c)
{
	int		i;
	char	operators[4];

	set_operators(operators);
	i = -1;
	while (operators[++i])
	{
		if (operators[i] == c)
			return (true);
	}
	return (false);
}
