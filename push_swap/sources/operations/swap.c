/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:40:57 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 13:45:15 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
	Takes stack, char indicating which stack and a flag

	Swap positions by setting:
		First:
			first->next = second->next;
			first->prev = second;

		Second:
			second->prev = NULL
			second->next = first;

	Set stack->top to second as its swapped
	If stack is 2 elements only, set first to be last

	Flag 0 if swap just ONE stack, 1 if swapping both
		1 is used only in swap_both function
*/
void	swap(t_stack *stack, char c, int flag)
{
	t_node	*first;
	t_node	*second;

	if (stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	first->prev = second;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	stack->top = second;
	if (stack->size == 2)
		stack->back = first;
	if (flag == 0)
		ft_printf("s%c\n", c);
	if (stack->dirty_index == 0)
		stack->dirty_index = 1;
}

void	swap_both(t_stack *a, t_stack *b)
{
	swap(a, 'a', 1);
	swap(b, 'b', 1);
	ft_printf("ss\n");
}
