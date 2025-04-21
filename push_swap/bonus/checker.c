/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:35:54 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/20 12:20:54 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	read_and_execute(t_stack *a, t_stack *b);
static void	push_c(t_stack *a, t_stack *b, char c);
static int	apply_instructions(t_stack *a, t_stack *b, char *line);

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (printf("%s\n", USAGE_B), 1);
	a = create_stack();
	b = create_stack();
	if (!a || !b)
		return (exit_clear(a, b), 1);
	if (check_input(a, argc, argv) == 1)
	{
		ft_printf("input error\n");
		return (ft_printf("Error\n"), exit_clear(a, b), 1);
	}
	if (!read_and_execute(a, b))
	{
		ft_printf("exec error\n");
		return (ft_printf("Error\n"), exit_clear(a, b), 1);
	}
	if (is_sorted(a) && b->size == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	exit_clear(a, b);
	return (0);
}

static int	read_and_execute(t_stack *a, t_stack *b)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(0);
			continue ;
		}
		if (!apply_instructions(a, b, line))
		{
			ft_printf("line: %s\n", line);
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	return (1);
}

static void	push_c(t_stack *a, t_stack *b, char c)
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
}

static int	apply_rotates(t_stack *a, t_stack *b, char *line);

static int	apply_instructions(t_stack *a, t_stack *b, char *line)
{
	if (!ft_strncmp(line, "sa\n", 3))
		swap(a, 'a', 1);
	else if (!ft_strncmp(line, "sb\n", 3))
		swap(b, 'b', 1);
	else if (!ft_strncmp(line, "ss\n", 3))
	{
		swap(a, 'a', 1);
		swap(b, 'b', 1);
	}
	else if (!ft_strncmp(line, "pa\n", 3))
		push_c(a, b, 'a');
	else if (!ft_strncmp(line, "pb\n", 3))
		push_c(a, b, 'b');
	else if (!apply_rotates(a, b, line))
		return (0);
	return (1);
}

static int	apply_rotates(t_stack *a, t_stack *b, char *line)
{
	if (!ft_strncmp(line, "ra\n", 3))
		rotate(a, 'a', 1);
	else if (!ft_strncmp(line, "rb\n", 3))
		rotate(b, 'b', 1);
	else if (!ft_strncmp(line, "rr\n", 3))
	{
		rotate(a, 'a', 1);
		rotate(b, 'b', 1);
	}
	else if (!ft_strncmp(line, "rra\n", 4))
		rev_rotate(a, 'a', 1);
	else if (!ft_strncmp(line, "rrb\n", 4))
		rev_rotate(b, 'b', 1);
	else if (!ft_strncmp(line, "rrr\n", 4))
	{
		rev_rotate(a, 'a', 1);
		rev_rotate(b, 'b', 1);
	}
	else
		return (0);
	return (1);
}
