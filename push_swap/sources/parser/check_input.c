/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:35:46 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 18:59:37 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	check_input(t_stack *a, int argc, char **argv)
{
	if (parse_input(a, argv, argc) == 1)
		return (1);
	else if (check_duplicates(a) == 1)
		return (1);
	return (0);
}
