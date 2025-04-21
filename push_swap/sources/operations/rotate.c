/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:36:54 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 13:45:04 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
	Takes stack, char indicating which stack and a flag

	Shifts all elements of the stack up by 1:
		The first element becomes the last one
	
		If the stack has less then 2 elements, do nothing

	Flag 0 if rotating just ONE stack, 1 if rotating both
		1 is used only in rotate_both function
*/
void	rotate(t_stack *stack, char c, int flag)
{
	t_node	*first;
	t_node	*last;

	if (stack->size < 2)
		return ;
	first = stack->top;
	last = stack->back;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
	stack->back = first;
	if (flag == 0)
		ft_printf("r%c\n", c);
	if (stack->dirty_index == 0)
		stack->dirty_index = 1;
}

void	rotate_both(t_stack *a, t_stack *b)
{
	rotate(a, 'a', 1);
	rotate(b, 'b', 1);
	ft_printf("rr\n");
}
