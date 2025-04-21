/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:11:23 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 15:20:06 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void		sort_five(t_stack *a, t_stack *b);

void	small_stack(t_stack *a, t_stack *b)
{
	if (a->size == 1)
		return ;
	else if (a->size == 2)
	{
		if (!is_sorted(a))
			swap(a, 'a', 0);
	}
	else if (a->size == 3)
		sort_three(a);
	else
		sort_five(a, b);
}

/*
	Make sure to place biggest value at the end of stack
	Check if stack is sorted, if not use sa
*/
void	sort_three(t_stack *a)
{
	long	av;
	long	bv;
	long	cv;

	av = a->top->value;
	bv = a->top->next->value;
	cv = a->back->value;
	if (is_sorted(a))
		return ;
	if (av > bv && av > cv)
		rotate(a, 'a', 0);
	else if (bv > av && bv > cv)
		rev_rotate(a, 'a', 0);
	if (!is_sorted(a))
		swap(a, 'a', 0);
}

static t_node	*find_smallest(t_stack *stack);

/*
	Sorts stacks of 4 and 5 elements
	1. Push 1 or 2 smallest to stack b
	2. Use sort_three on stack a
	3. Push from b to a
*/
static void	sort_five(t_stack *a, t_stack *b)
{
	t_node	*smallest;
	int		start_size;

	start_size = a->size;
	if (is_sorted(a))
		return ;
	while (a->size != 3)
	{
		if (a->dirty_index == 1)
			set_indexes(a);
		smallest = find_smallest(a);
		if (smallest->index > a->size / 2)
			while (a->top != smallest)
				rev_rotate(a, 'a', 0);
		else
			while (a->top != smallest)
				rotate(a, 'a', 0);
		if (a->size == start_size && is_sorted(a))
			return ;
		push(a, b, 'b');
	}
	sort_three(a);
	while (a->size != start_size)
		push(a, b, 'a');
}

static t_node	*find_smallest(t_stack *stack)
{
	t_node	*current;
	t_node	*smallest;

	smallest = stack->top;
	current = stack->top->next;
	while (current)
	{
		if (current->value < smallest->value)
			smallest = current;
		current = current->next;
	}
	return (smallest);
}
