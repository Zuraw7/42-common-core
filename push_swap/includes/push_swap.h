/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:49 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/20 11:56:52 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include "./libft/libft.h"

# define USAGE "Wrong usage!\nUse: ./push_swap \"1 2 3 4 ...\" or \
				\n     ./push_swap 1 2 3 4 ... "
# define USAGE_B "Wrong usage!\nUse: ./checker \"1 2 3 4 ...\" or \
				\n     ./push_swap 1 2 3 4 ... "
# define HASH_SIZE 509

/*******	Structs	*******/
typedef struct s_node		t_node;
typedef struct s_stack		t_stack;
typedef struct s_hash_node	t_hash_node;
typedef struct s_hash_table	t_hash_table;

typedef struct s_node
{
	long	value;
	int		index;
	int		cost;
	int		src_m;
	int		dest_m;
	bool	cheapest;
	t_node	*next;
	t_node	*prev;
	t_node	*target;
}	t_node;

/*
	Dirty index is a flag that determines if indexes are in a proper order
	I need indexes to calculate moves
	It also prevents from spamming set_indexes which works in O(n)
*/
typedef struct s_stack
{
	int		size;
	int		dirty_index;
	t_node	*top;
	t_node	*back;
}	t_stack;

typedef struct s_hash_node
{
	int			value;
	t_hash_node	*next;
}	t_hash_node;

typedef struct s_hash_table
{
	t_hash_node	*table[HASH_SIZE];
}	t_hash_table;

/*******	Sources	*******/
// general_utils.c
void	exit_clear(t_stack *a, t_stack *b);
bool	is_sorted(t_stack *stack);

/*******	Nodes	*******/
// nodes_utils.c
t_node	*create_node(long value);
void	insert_back(t_stack *stack, t_node *node);
void	set_indexes(t_stack *stack);

/*******	Stacks	*******/
// stacks_utils.c
t_stack	*create_stack(void);
void	print_stack(t_stack *stack);

/*******	Operations	*******/
// swap.c
void	swap(t_stack *stack, char c, int flag);
void	swap_both(t_stack *a, t_stack *b);

// push.c
void	push(t_stack *a, t_stack *b, char c);
int		uniq_push(t_stack *src, t_stack *dest);

// rotate.c
void	rotate(t_stack *stack, char c, int flag);
void	rotate_both(t_stack *a, t_stack *b);

// rev_rotate.c
void	rev_rotate(t_stack *stack, char c, int flag);
void	rev_rotate_both(t_stack *a, t_stack *b);

/*******	Parser	*******/
// parse_input.c
int		parse_input(t_stack *a, char **argv, int argc);
int		parse_single_numbers(t_stack *a, char **argv);
int		parse_string(t_stack *a, char *numbers);

// check_duplicates.c
int		hash_insert(t_hash_table *hash, int value);
void	free_hash_table(t_hash_table *hash);
int		check_duplicates(t_stack *stack);

// check_input.c
int		check_input(t_stack *a, int argc, char **argv);

/*******	Sort	*******/
// run_sort.c
void	run_sort(t_stack *a, t_stack *b);

// small_stack.c
void	small_stack(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);

// sort_utils.c
t_node	*get_cheapest(t_stack *stack);
t_node	*find_min(t_stack *stack);
void	calculate_cost(t_stack *src, t_stack *dest);

// turk_sort.c
void	turk_sort(t_stack *a, t_stack *b);

// find_targets.c
void	find_targets_a(t_stack *a, t_stack *b);
void	find_targets_b(t_stack *a, t_stack *b);

// align_stacks.c
void	align_stacks(t_stack *src, t_stack *dest, t_node *cheapest,
			char dest_id);

#endif