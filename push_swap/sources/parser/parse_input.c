/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:46:00 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/18 13:36:29 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	parse_input(t_stack *a, char **argv, int argc)
{
	if (argc == 2)
		return (parse_string(a, argv[1]));
	else
		return (parse_single_numbers(a, &argv[1]));
}

int	parse_single_numbers(t_stack *a, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		insert_back(a, create_node(ft_atoi(argv[i])));
		if (a->back->value > INT_MAX || a->back->value < INT_MIN)
			return (1);
		i++;
	}
	set_indexes(a);
	return (0);
}

static int	check_is_number(char *str, int end);

int	parse_string(t_stack *a, char *numbers)
{
	int		i;
	int		start;
	char	*num;

	i = 0;
	start = 0;
	while (numbers[i])
	{
		if (numbers[i] == ' ')
			i++;
		if (!numbers[i])
			break ;
		start = i;
		while (numbers[i] && numbers[i] != ' ')
			i++;
		if (check_is_number(&numbers[start], i - start) == 1)
			return (1);
		num = ft_substr(numbers, start, i - start);
		insert_back(a, create_node(ft_atoi(num)));
		if (a->back->value > INT_MAX || a->back->value < INT_MIN)
			return (1);
		free(num);
	}
	set_indexes(a);
	return (0);
}

static int	check_is_number(char *str, int end)
{
	int	i;

	i = 0;
	if (end == 0)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < end)
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
