/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:05:56 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/08 20:26:25 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// ADDS ENEMY AND ITS LOCATION TO LINKED LIST
static void	add_enemy(t_enemies **enemy, int x, int y)
{
	t_enemies	*new_enemy;
	t_enemies	*last_elem;

	new_enemy = malloc(sizeof(t_enemies));
	if (!new_enemy)
	{
		ft_printf("Failed to add enemy\n");
		exit(1);
	}
	new_enemy->x = x;
	new_enemy->y = y;
	new_enemy->next = NULL;
	if (*enemy == NULL)
		*enemy = new_enemy;
	else
	{
		last_elem = *enemy;
		while (last_elem->next != NULL)
			last_elem = last_elem->next;
		last_elem->next = new_enemy;
	}
}

// LOOKS FOR ENEMIES AND RUNS ADD_ENEMY IF FOUND
void	set_enemies(t_data *data)
{
	int			y;
	int			x;
	char		**map;
	t_enemies	*enemies;

	enemies = NULL;
	map = data->map.map_data;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'W')
				add_enemy(&enemies, x, y);
			x++;
		}
		y++;
	}
	data->enemies = enemies;
}

static void	put_lose_string(t_data *data)
{
	int	color;
	int	mid_x;
	int	mid_y;

	color = 0x00FFFFFF;
	mid_x = (data->map.map_width * TILE_SIZE) / 2 - 64;
	mid_y = (data->map.map_height * TILE_SIZE) / 2;
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x, mid_y, color, "You lost. Press ESC to leave");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x + 1, mid_y, color, "You lost. Press ESC to leave");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x, mid_y + 1, color, "You lost. Press ESC to leave");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x + 1, mid_y + 1, color, "You lost. Press ESC to leave");
}

// IF ENEMY XY AND PLAYER XY ARE THE SAME PLAYER LOSE
void	check_if_lose(int keysym, t_data *data)
{
	t_enemies	*enemy;
	t_player	player;

	player = data->player;
	enemy = data->enemies;
	while (enemy)
	{
		if (player.pos_x == enemy->x && player.pos_y == enemy->y)
		{
			data->game_on = 1;
			put_lose_string(data);
			if (keysym == 65293)
			{
				do_destroy(data);
				exit(0);
			}
		}
		enemy = enemy->next;
	}
}

// FREES ENEMIES MEMMORY
void	free_all_enemies(t_data *data)
{
	t_enemies	*current;
	t_enemies	*next;

	current = data->enemies;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	data->enemies = NULL;
}
