/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_targets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:16:35 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 14:17:46 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static t_node	*find_max(t_stack *stack)
{
	t_node	*max;
	t_node	*current;

	max = stack->top;
	current = stack->top->next;
	while (current)
	{
		if (current->value > max->value)
			max = current;
		current = current->next;
	}
	return (max);
}

void	find_targets_a(t_stack *a, t_stack *b)
{
	t_node	*in_a;
	t_node	*in_b;
	t_node	*closest_node;
	long	closest_value;

	in_a = a->top;
	while (in_a)
	{
		in_b = b->top;
		closest_node = NULL;
		closest_value = LONG_MIN;
		while (in_b)
		{
			if (in_b->value <= in_a->value && in_b->value > closest_value)
			{
				closest_value = in_b->value;
				closest_node = in_b;
			}
			in_b = in_b->next;
		}
		if (!closest_node)
			closest_node = find_max(b);
		in_a->target = closest_node;
		in_a = in_a->next;
	}
}

void	find_targets_b(t_stack *a, t_stack *b)
{
	t_node	*in_b;
	t_node	*in_a;
	t_node	*closest_node;
	long	closest_value;

	in_b = b->top;
	while (in_b)
	{
		in_a = a->top;
		closest_node = NULL;
		closest_value = LONG_MAX;
		while (in_a)
		{
			if (in_a->value >= in_b->value && in_a->value < closest_value)
			{
				closest_value = in_a->value;
				closest_node = in_a;
			}
			in_a = in_a->next;
		}
		if (!closest_node)
			closest_node = find_min(a);
		in_b->target = closest_node;
		in_b = in_b->next;
	}
}
