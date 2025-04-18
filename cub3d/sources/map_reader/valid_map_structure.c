/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:05:25 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/19 09:22:20 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_set(char **map, char *set);
static int	validate_structure(t_map *map, char *set, int *p_pos);
static int	validate_position_count(int p_pos);

/*
	1. Stworzenie setu {'0', '1', 'N', 'E', 'S', 'W'}
	2. Sprawdzenie czy mapa składa się tylko z tego setu
	3. Sprawdzenie czy mapa nie ma innego elementu niż 0, 1, N, E, S, W, ' '
	4. Sprawdzenie czy nie ma pustych luk w mapie
		111111
		100001
		10 001
		100001
		111111
		Powyższa mapa jest nieakceptowana
	5. Sprawdzenie czy jest tylko jedna pozycja startowa
*/
int	valid_map_structure(t_map *map)
{
	char	*set;
	int		p_pos;

	set = make_set("01NESW");
	if (!set)
		return (1);
	p_pos = 0;
	if (validate_set(map->map, set)
		|| validate_structure(map, set, &p_pos)
		|| validate_position_count(p_pos))
		return (free(set), 1);
	calc_width_height(map);
	return (free(set), 0);
}

static int	validate_set(char **map, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(set, map[i][j]) && map[i][j] != ' ' &&
				map[i][j] != '\n')
			{
				printf("Line after map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
	Sprawdza czy dany element mapy zawiera się w SET
	Jeżeli nie to sprawdza czy wsztsct sąsiedzi są w SET
		- jeśli są to oznacza że jest to niechciany element mapy
		- jeżeli nie to oznacza że jest to poza mapą
	Ma to na celu zabezpieczenie się przed lukami w mapie poza granicami
*/
static int	validate_structure(t_map *map, char *set, int *p_pos)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (!ft_strchr(set, map->map[i][j]) &&
				check_neighbour(map->map, set, i, j) == 4)
				return (1);
			count_p_pos(map, i, j, p_pos);
			j++;
		}
		i++;
	}
	return (0);
}

static int	validate_position_count(int p_pos)
{
	if (p_pos != 1)
	{
		printf("Error: There is not 1 player position\n");
		return (1);
	}
	return (0);
}
