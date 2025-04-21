/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:18:17 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 14:35:21 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	set_hash_index(int value);

int	hash_insert(t_hash_table *hash, int value)
{
	int			index;
	t_hash_node	*curr;
	t_hash_node	*new_node;

	index = set_hash_index(value);
	curr = hash->table[index];
	while (curr)
	{
		if (curr->value == value)
			return (1);
		curr = curr->next;
	}
	new_node = malloc(sizeof(t_hash_node));
	if (!new_node)
	{
		ft_printf("Error allocating node in hashtable\n");
		exit(1);
	}
	new_node->value = value;
	new_node->next = hash->table[index];
	hash->table[index] = new_node;
	return (0);
}

static int	set_hash_index(int value)
{
	if (value < 0)
		value = -value;
	return (value % HASH_SIZE);
}

void	free_hash_table(t_hash_table *hash)
{
	t_hash_node	*curr;
	t_hash_node	*temp;
	int			i;

	i = 0;
	while (i < HASH_SIZE)
	{
		curr = hash->table[i];
		while (curr)
		{
			temp = curr;
			curr = curr->next;
			free(temp);
		}
		i++;
	}
	free(hash);
}

int	check_duplicates(t_stack *stack)
{
	t_node			*temp;
	t_hash_table	*hash;
	int				i;

	temp = stack->top;
	hash = malloc(sizeof(t_hash_table));
	if (!hash)
		return (1);
	i = -1;
	while (++i < HASH_SIZE)
		hash->table[i] = NULL;
	while (temp)
	{
		if (hash_insert(hash, temp->value) == 1)
		{
			ft_printf("Duplicate value: %d\n", temp->value);
			free_hash_table(hash);
			return (1);
		}
		temp = temp->next;
	}
	free_hash_table(hash);
	return (0);
}
