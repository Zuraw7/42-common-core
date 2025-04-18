/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:48:42 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/04 13:03:11 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_commas(char *line);
static int	check_is_number(char *line);
static int	check_rgb_values(char *line);
static void	set_rgb(t_map *map);

/*
	2. Kolory
		a. sprawdza czy są 2 przecinki (3 liczby)
		b. czy każda wartość jest liczbą
		c. każda wartość mieści się w przedziale od 0 do 255
		d. przypisuje wartość RGBA do ceiling_color i floor_color
*/
int	check_colors(t_map *map)
{
	int	i;

	i = 0;
	while (map->hold_cf_color[i])
	{
		if (count_commas(map->hold_cf_color[i]) != 2)
			return (1);
		if (check_is_number(map->hold_cf_color[i]))
			return (1);
		if (check_rgb_values(map->hold_cf_color[i]))
			return (1);
		i++;
	}
	set_rgb(map);
	return (0);
}

static int	count_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		printf("Error: Wrong amount of commas\n");
	return (count);
}

static int	check_is_number(char *line)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\v\f\r\n");
	i = 0;
	while (trimmed[i])
	{
		if (ft_isdigit(trimmed[i]))
			i++;
		else if (trimmed[i] == ',')
			i++;
		else if (trimmed[i] == '-' && ft_isdigit(trimmed[i + 1]))
			i++;
		else
		{
			printf("Error: Not a number [%c]\n", trimmed[i]);
			free(trimmed);
			return (1);
		}
	}
	free(trimmed);
	return (0);
}

static int	check_rgb_values(char *line)
{
	int		i;
	char	*trimmed;
	char	**split;

	trimmed = ft_strtrim(line, " \t\v\f\r\n");
	split = ft_split(trimmed, ',');
	if (!split || !trimmed)
		return (1);
	i = 0;
	while (split[i])
	{
		if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
		{
			printf("Error: Value out of range [%d]\n", ft_atoi(split[i]));
			free_double_arr(split);
			free(trimmed);
			return (1);
		}
		i++;
	}
	free_double_arr(split);
	free(trimmed);
	return (0);
}

static void	set_rgb(t_map *map)
{
	char	**split_c;
	char	**split_f;
	char	*trimmed_c;
	char	*trimmed_f;

	trimmed_c = ft_strtrim(map->hold_cf_color[0], " \t\v\f\r\n");
	split_c = ft_split(trimmed_c, ',');
	trimmed_f = ft_strtrim(map->hold_cf_color[1], " \t\v\f\r\n");
	split_f = ft_split(trimmed_f, ',');
	if (!split_c || !split_f || !trimmed_c || !trimmed_f)
	{
		perror("Error allocating memory in set_rgb");
		return ;
	}
	map->ceiling_color = get_argb(255, ft_atoi(split_c[0]),
			ft_atoi(split_c[1]), ft_atoi(split_c[2]));
	map->floor_color = get_argb(255, ft_atoi(split_f[0]),
			ft_atoi(split_f[1]), ft_atoi(split_f[2]));
	free_double_arr(split_c);
	free(trimmed_c);
	free_double_arr(split_f);
	free(trimmed_f);
}
