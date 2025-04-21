/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:33:20 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 21:12:09 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	clear_stack(t_stack *stack);

// Stack B should be empty at the end!
void	exit_clear(t_stack *a, t_stack *b)
{
	clear_stack(a);
	clear_stack(b);
}

static void	clear_stack(t_stack *stack)
{
	t_node	*to_free;
	t_node	*temp;

	if (stack)
	{
		if (stack->size != 0)
		{
			to_free = stack->top;
			while (to_free != NULL)
			{
				temp = to_free->next;
				free(to_free);
				to_free = temp;
			}
		}
		free(stack);
	}
}

bool	is_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->top->next;
	while (current)
	{
		if (current->value < current->prev->value)
			return (false);
		current = current->next;
	}
	return (true);
}
