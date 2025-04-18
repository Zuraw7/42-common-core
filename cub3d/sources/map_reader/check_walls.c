/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:34:54 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/04 13:33:15 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_border_surrounded(t_bfs *tmp, t_map *map, char **tmp_map);
static int	is_space(t_bfs *tmp, char **tmp_map);
static int	add_to_queue(t_map *map, int x, int y, char **tmp_map);
static void	add_neighbors_to_queue(t_bfs *tmp, t_map *map, char **tmp_map);

/*
	1. Zduplikowanie mapy do tmp_map
	2. Stworzenie kolejki do BFS -> zaczynając od pola startowego gracza
		a. ustawienie sprawdzonych pól na B
	3. Sprawdzenie sąsiednich pól pod kątem ścian
		a. Jeżeli sąsienie pole nie jest ścianą -> daje do kolejki
		c. jeżeli aktualne pole jest na brzegu mapy (krańce mapy) lub
			obok jest spacja -> zwraca błąd
	4. Zwolnienie pamięci -> mapy i kolejki
*/
int	check_walls(t_map *map)
{
	char	**tmp_map;
	t_bfs	*tmp;

	map->queue = init_queue(map->data->player->x, map->data->player->y);
	if (!map->queue)
		return (printf("Error allocating BFS queue"), 1);
	tmp_map = bfs_map(map);
	tmp = map->queue;
	while (tmp)
	{
		if (!is_border_surrounded(tmp, map, tmp_map) || is_space(tmp, tmp_map))
		{
			free_double_arr(tmp_map);
			clear_queue(map->queue);
			return (1);
		}
		add_neighbors_to_queue(tmp, map, tmp_map);
		tmp = tmp->next;
	}
	free_double_arr(tmp_map);
	clear_queue(map->queue);
	return (0);
}

static int	is_border_surrounded(t_bfs *tmp, t_map *map, char **tmp_map)
{
	if (tmp->y == 0 || tmp->y == map->height - 1)
	{
		if (tmp_map[tmp->y][tmp->x] != '1')
		{
			printf("Error: Map is not surrounded by walls at (%d, %d)\n",
				tmp->x, tmp->y);
			return (0);
		}
	}
	if (tmp->x == 0 || tmp->x == (int)ft_strlen(tmp_map[tmp->y]) - 1)
	{
		if (tmp_map[tmp->y][tmp->x] != '1')
		{
			printf("Error: Map is not surrounded by walls at (%d, %d)\n",
				tmp->x, tmp->y);
			return (0);
		}
	}
	return (1);
}

static int	is_space(t_bfs *tmp, char **tmp_map)
{
	if (tmp_map[tmp->y][tmp->x] == ' ')
	{
		printf("Error: Map is not surrounded by walls\n");
		return (1);
	}
	return (0);
}

static int	add_to_queue(t_map *map, int x, int y, char **tmp_map)
{
	t_bfs	*new;
	t_bfs	*tmp;

	if (tmp_map[y][x] == 'B' || tmp_map[y][x] == '1')
		return (0);
	new = init_queue(x, y);
	if (!new)
		return (1);
	tmp = map->queue;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp_map[y][x] = 'B';
	return (0);
}

static void	add_neighbors_to_queue(t_bfs *tmp, t_map *map, char **tmp_map)
{
	if (tmp->x - 1 >= 0
		&& tmp_map[tmp->y][tmp->x - 1] != '1'
		&& tmp_map[tmp->y][tmp->x - 1] != 'B')
		add_to_queue(map, tmp->x - 1, tmp->y, tmp_map);
	if (tmp->x + 1 < (int)ft_strlen(tmp_map[tmp->y])
		&& tmp_map[tmp->y][tmp->x + 1] != '1'
		&& tmp_map[tmp->y][tmp->x + 1] != 'B')
		add_to_queue(map, tmp->x + 1, tmp->y, tmp_map);
	if (tmp->y - 1 >= 0
		&& tmp_map[tmp->y - 1][tmp->x] != '1'
		&& tmp_map[tmp->y - 1][tmp->x] != 'B')
		add_to_queue(map, tmp->x, tmp->y - 1, tmp_map);
	if (tmp->y + 1 < map->height
		&& tmp_map[tmp->y + 1][tmp->x] != '1'
		&& tmp_map[tmp->y + 1][tmp->x] != 'B')
		add_to_queue(map, tmp->x, tmp->y + 1, tmp_map);
}
