/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:37:00 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 13:44:50 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
	Takes stack, char indicating which stack and a flag

	Shifts all elements of the stack down by 1:
		The last element becomes the first one
	
		If the stack has less then 2 elements, do nothing

	Flag 0 if rev rotating just ONE stack, 1 if rev rotating both
		1 is used only in rev_rotate_both function
*/
void	rev_rotate(t_stack *stack, char c, int flag)
{
	t_node	*first;
	t_node	*last;

	if (stack->size < 2)
		return ;
	first = stack->top;
	last = stack->back;
	stack->back = last->prev;
	stack->back->next = NULL;
	last->prev = NULL;
	last->next = first;
	first->prev = last;
	stack->top = last;
	if (flag == 0)
		ft_printf("rr%c\n", c);
	if (stack->dirty_index == 0)
		stack->dirty_index = 1;
}

void	rev_rotate_both(t_stack *a, t_stack *b)
{
	rev_rotate(a, 'a', 1);
	rev_rotate(b, 'b', 1);
	ft_printf("rrr\n");
}
