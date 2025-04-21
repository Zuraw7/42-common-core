/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:04:35 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 14:26:19 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_node	*get_cheapest(t_stack *stack)
{
	t_node	*cheapest;
	t_node	*current;

	current = stack->top;
	cheapest = stack->top;
	while (current)
	{
		current->cheapest = false;
		if (current->cost < cheapest->cost)
			cheapest = current;
		current = current->next;
	}
	cheapest->cheapest = true;
	return (cheapest);
}

t_node	*find_min(t_stack *stack)
{
	t_node	*min;
	t_node	*current;

	min = stack->top;
	current = stack->top->next;
	while (current)
	{
		if (current->value < min->value)
			min = current;
		current = current->next;
	}
	return (min);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_abs(int a)
{
	if (a < 0)
		a = -a;
	return (a);
}

void	calculate_cost(t_stack *src, t_stack *dest)
{
	t_node	*in_src;
	t_node	*target;

	in_src = src->top;
	while (in_src)
	{
		target = in_src->target;
		if (in_src->index <= src->size / 2)
			in_src->src_m = in_src->index;
		else
			in_src->src_m = -(src->size - in_src->index);
		if (target->index <= dest->size / 2)
			in_src->dest_m = target->index;
		else
			in_src->dest_m = -(dest->size - target->index);
		if ((in_src->src_m >= 0 && in_src->dest_m >= 0)
			|| (in_src->src_m < 0 && in_src->dest_m < 0))
			in_src->cost = ft_max(ft_abs(in_src->src_m),
					ft_abs(in_src->dest_m));
		else
			in_src->cost = ft_abs(in_src->src_m) + ft_abs(in_src->dest_m);
		in_src = in_src->next;
	}
}
