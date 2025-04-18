/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_structure_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:49:57 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 22:35:36 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	process_row(char *row, int *in_map, int current_width);

// sprawdza czy sąsiedzi są w SET
int	check_neighbour(char **map, char *set, int i, int j)
{
	int	walls;

	walls = 0;
	if (j > 0 && ft_strchr(set, map[i][j - 1]))
		walls++;
	if (j + 1 < (int)ft_strlen(map[i])
		&& ft_strchr(set, map[i][j + 1]))
		walls++;
	if (i > 0 && j < (int)ft_strlen(map[i - 1])
		&& ft_strchr(set, map[i - 1][j]))
		walls++;
	if (map[i + 1] && j < (int)ft_strlen(map[i + 1])
		&& ft_strchr(set, map[i + 1][j]))
		walls++;
	return (walls);
}

void	count_p_pos(t_map *map, int i, int j, int *pp)
{
	if (map->map[i][j] == 'N' || map->map[i][j] == 'E'
			|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
	{
		(*pp)++;
		if (*pp == 1)
		{
			map->data->player->start_dir = map->map[i][j];
			map->data->player->x = j + 0.5;
			map->data->player->y = i;
			set_player_dir(map->data->player);
		}
	}
}

void	calc_width_height(t_map *map)
{
	int		i;
	int		in_map;
	char	*trimmed;

	i = 0;
	in_map = 0;
	while (map->map[i])
	{
		trimmed = ft_strtrim(map->map[i], " \t\v\r\n");
		map->width = process_row(map->map[i], &in_map, map->width);
		if (map->width == -1)
			return ;
		if (ft_strlen(trimmed) == 0)
			break ;
		free(trimmed);
		trimmed = NULL;
		i++;
	}
	if (trimmed)
		free(trimmed);
	map->height = i;
}

static int	process_row(char *row, int *in_map, int current_width)
{
	int		j;
	char	*trimmed;

	trimmed = ft_strtrim(row, " \t\v\r\n");
	if (!trimmed)
		return (-1);
	j = 0;
	while (row[j])
	{
		if (row[j] == '1')
			*in_map = 1;
		if (*in_map && (row[j] == ' ' || row[j] == '\n'))
			break ;
		j++;
	}
	if (j > current_width)
		current_width = j;
	free(trimmed);
	return (current_width);
}
