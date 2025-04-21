/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:13:59 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 14:37:46 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	manage_a(t_stack *a, t_stack *b);
static void	manage_b(t_stack *a, t_stack *b);
static void	put_smallest_at_top(t_stack *a);

/*
	How it works:
	1. Push first 2 nodes to stack B
	2. For each node in stack A find closest smaller value in stack B
		- if there are only bigger, choose biggest of all in B
	3. Calculate how many moves it takes to put node above it's target
	4. Push the cheapest
	5. Repeat until stack A has 3 nodes only
	6. Use sort_three to sort stack A
	7. Now for each node in stack B find closest bigger value in stack A
		- if there are smaller only, choose the smallest of all in A
	8. Calculate how many moves it takes to put node above it's target
	9. Push the cheapest
	10. Repeat until stack B is empty
	11. If stack A is not sorted
		- find the smallest value in stack, and put it at the top
*/
void	turk_sort(t_stack *a, t_stack *b)
{
	push(a, b, 'b');
	push(a, b, 'b');
	manage_a(a, b);
	sort_three(a);
	manage_b(a, b);
	if (!is_sorted(a))
		put_smallest_at_top(a);
}

/*
	1. Sets proper indexes in both stacks
	2. Find targets for all nodes in A
	3. Calculate each node's cost to be in proper position
	4. Get cheapest node
	5. Put it and its target on top of stacks
	6. Push to B
*/
static void	manage_a(t_stack *a, t_stack *b)
{
	t_node	*cheapest;

	while (a->size != 3)
	{
		set_indexes(a);
		set_indexes(b);
		find_targets_a(a, b);
		calculate_cost(a, b);
		cheapest = get_cheapest(a);
		align_stacks(a, b, cheapest, 'b');
		push(a, b, 'b');
	}
}

/*
	1. Sets proper indexes in both stacks
	2. Find targets for all nodes in B
	3. Calculate each node's cost to be in proper position
	4. Get cheapest node
	5. Put it and its target on top of stacks
	6. Push to A
*/
static void	manage_b(t_stack *a, t_stack *b)
{
	t_node	*cheapest;

	while (b->size != 0)
	{
		set_indexes(a);
		set_indexes(b);
		find_targets_b(a, b);
		calculate_cost(b, a);
		cheapest = get_cheapest(b);
		align_stacks(b, a, cheapest, 'a');
		push(a, b, 'a');
	}
}

static void	put_smallest_at_top(t_stack *a)
{
	t_node	*min;

	set_indexes(a);
	min = find_min(a);
	while (a->top != min)
	{
		if (min->index <= a->size / 2)
			rotate(a, 'a', 0);
		else
			rev_rotate(a, 'a', 0);
	}
}
