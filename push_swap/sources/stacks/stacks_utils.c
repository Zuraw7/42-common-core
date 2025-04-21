/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:32:09 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 10:05:48 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_stack	*create_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
	{
		ft_printf("Error allocating stack\n");
		return (NULL);
	}
	stack->size = 0;
	stack->dirty_index = 0;
	stack->top = NULL;
	stack->back = NULL;
	return (stack);
}

void	print_stack(t_stack *stack)
{
	t_node	*in_stack;

	in_stack = stack->top;
	while (in_stack != NULL)
	{
		ft_printf("value: %d\n", in_stack->value);
		in_stack = in_stack->next;
	}
}
