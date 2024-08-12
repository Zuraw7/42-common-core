/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:57:36 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:55:29 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Absolute number
static int	ft_abs(int x)
{
	if (x < 0)
		return (x *= -1);
	return (x);
}

// Checks if move is possible
static int	is_valid_move(char **map, int x, int y)
{
	if (map[y][x] != '1' && map[y][x] != 'W'
		&& map[y][x] != 'C' && map[y][x] != 'E')
		return (1);
	return (0);
}

static void	x_axis_move(int delta_x, int delta_y, t_enemies **enemy, char **map)
{
	if (delta_x > 0 && is_valid_move(map, (*enemy)->x + 1, (*enemy)->y))
		(*enemy)->x += 1;
	else if (delta_x < 0 && is_valid_move(map, (*enemy)->x - 1, (*enemy)->y))
		(*enemy)->x -= 1;
	else if (delta_y > 0 && is_valid_move(map, (*enemy)->x, (*enemy)->y + 1))
		(*enemy)->y += 1;
	else if (delta_y < 0 && is_valid_move(map, (*enemy)->x, (*enemy)->y - 1))
		(*enemy)->y -= 1;
}

static void	y_axis_move(int delta_x, int delta_y, t_enemies **enemy, char **map)
{
	if (delta_y > 0 && is_valid_move(map, (*enemy)->x, (*enemy)->y + 1))
		(*enemy)->y += 1;
	else if (delta_y < 0 && is_valid_move(map, (*enemy)->x, (*enemy)->y - 1))
		(*enemy)->y -= 1;
	else if (delta_x > 0 && is_valid_move(map, (*enemy)->x + 1, (*enemy)->y))
		(*enemy)->x += 1;
	else if (delta_x < 0 && is_valid_move(map, (*enemy)->x - 1, (*enemy)->y))
		(*enemy)->x -= 1;
}

// Moves enemies towards the player
void	move_towards_player(t_data *data)
{
	int			delta_x;
	int			delta_y;
	t_enemies	*enemy;
	char		**map;

	map = data->map.map_data;
	enemy = data->enemies;
	while (enemy)
	{
		delta_x = data->player.pos_x - enemy->x;
		delta_y = data->player.pos_y - enemy->y;
		data->map.map_data[enemy->y][enemy->x] = '0';
		if (ft_abs(delta_x) > ft_abs(delta_y))
			x_axis_move(delta_x, delta_y, &enemy, map);
		else
			y_axis_move(delta_x, delta_y, &enemy, map);
		data->map.map_data[enemy->y][enemy->x] = 'W';
		enemy = enemy->next;
	}
}
