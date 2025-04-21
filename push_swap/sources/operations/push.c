/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:11:34 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/20 11:56:32 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/*
	Takes two stacks: src and dest

	Moves the first element from the top of src to the top of dest
	Does nothing and returns 1 if src is empty
	Return 0 on success

	Take dest->top and assign it to temp

	If dest is empty:
		Set temp->prev = NULL
		Set temp->next = NULL
		Set dest->top and dest->back to temp
	
	If dest is not empty:
		Set temp->next = dest->top
		Set temp->prev = NULL
		Set dest->top->prev = temp
		Set dest->top = temp

	Always decrement src->size and increment dest->size
*/
int	uniq_push(t_stack *src, t_stack *dest)
{
	t_node	*temp;

	if (src->size == 0)
		return (1);
	temp = src->top;
	src->top = src->top->next;
	if (src->top)
		src->top->prev = NULL;
	src->size--;
	if (dest->size == 0)
	{
		temp->prev = NULL;
		temp->next = NULL;
		dest->top = temp;
		dest->back = temp;
	}
	else
	{
		temp->next = dest->top;
		temp->prev = NULL;
		dest->top->prev = temp;
		dest->top = temp;
	}
	dest->size++;
	return (0);
}

/*
	Takes two stacks and char that tells to which stack should be pushed 
	i.e. push(a, b, 'a'), will do pa -> from stack B to stack A
*/
void	push(t_stack *a, t_stack *b, char c)
{
	if (c == 'a')
	{
		if (uniq_push(b, a) == 1)
		{
			ft_printf("Stack b is empty, cannot push\n");
			return ;
		}
		if (a->dirty_index == 0)
			a->dirty_index = 1;
	}
	else
	{
		if (uniq_push(a, b) == 1)
		{
			ft_printf("Stack a is empty, cannot push\n");
			return ;
		}
		if (b->dirty_index == 0)
			b->dirty_index = 1;
	}
	ft_printf("p%c\n", c);
}
