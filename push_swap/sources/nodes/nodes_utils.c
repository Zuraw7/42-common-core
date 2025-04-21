/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:31:25 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/19 13:38:11 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_node	*create_node(long value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		ft_printf("Error allocating node\n");
		return (NULL);
	}
	node->value = value;
	node->cost = 0;
	node->index = 0;
	node->src_m = 0;
	node->dest_m = 0;
	node->cheapest = false;
	node->next = NULL;
	node->prev = NULL;
	node->target = NULL;
	return (node);
}

void	insert_back(t_stack *stack, t_node *node)
{
	if (stack->size == 0)
	{
		stack->top = node;
		stack->back = node;
	}
	else
	{
		stack->back->next = node;
		node->prev = stack->back;
		stack->back = node;
	}
	stack->size++;
}

// Set indexes from start and end so it takes twice less operations
void	set_indexes(t_stack *stack)
{
	t_node	*front;
	t_node	*back;
	int		i;
	int		j;

	front = stack->top;
	back = stack->back;
	i = 0;
	j = stack->size - 1;
	while (front && back && i <= j)
	{
		if (i == j)
		{
			front->index = i;
			break ;
		}
		front->index = i;
		back->index = j;
		front = front->next;
		back = back->prev;
		i++;
		j--;
	}
	stack->dirty_index = 0;
}
