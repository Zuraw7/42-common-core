/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:21:05 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 14:27:19 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	rot_both(t_stack *src, t_stack *dest, t_node *cheapest);
static void	rot_src(t_stack *src, t_node *cheapest, char id);
static void	rot_dest(t_stack *dest, t_node *cheapest, char id);

/*
	Function puts cheapest and it's target on top of stacks
*/
void	align_stacks(t_stack *src, t_stack *dest,
	t_node *cheapest, char dest_id)
{
	char	src_id;

	if (dest_id == 'a')
		src_id = 'b';
	else
		src_id = 'a';
	rot_both(src, dest, cheapest);
	rot_src(src, cheapest, src_id);
	rot_dest(dest, cheapest, dest_id);
}

// Use rr or rrr
static void	rot_both(t_stack *src, t_stack *dest, t_node *cheapest)
{
	while (cheapest->src_m > 0 && cheapest->dest_m > 0)
	{
		rotate_both(src, dest);
		cheapest->src_m--;
		cheapest->dest_m--;
	}
	while (cheapest->src_m < 0 && cheapest->dest_m < 0)
	{
		rev_rotate_both(src, dest);
		cheapest->src_m++;
		cheapest->dest_m++;
	}
}

// Put cheapest on top of a stack
static void	rot_src(t_stack *src, t_node *cheapest, char id)
{
	while (cheapest->src_m > 0)
	{
		rotate(src, id, 0);
		cheapest->src_m--;
	}
	while (cheapest->src_m < 0)
	{
		rev_rotate(src, id, 0);
		cheapest->src_m++;
	}
}

// Put target of cheapest on top of a stack
static void	rot_dest(t_stack *dest, t_node *cheapest, char id)
{
	while (cheapest->dest_m > 0)
	{
		rotate(dest, id, 0);
		cheapest->dest_m--;
	}
	while (cheapest->dest_m < 0)
	{
		rev_rotate(dest, id, 0);
		cheapest->dest_m++;
	}
}
