/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:03:35 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 14:23:31 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (printf("%s\n", USAGE), 1);
	a = create_stack();
	b = create_stack();
	if (!a || !b)
	{
		exit_clear(a, b);
		return (1);
	}
	if (check_input(a, argc, argv) == 1)
	{
		ft_printf("Error\n");
		exit_clear(a, b);
		return (1);
	}
	run_sort(a, b);
	exit_clear(a, b);
	return (0);
}
