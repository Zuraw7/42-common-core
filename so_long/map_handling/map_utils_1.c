/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:48:47 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 16:57:05 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// ADDS COLLECTIBLE/PLAYER/ENEMY/EXIT TO MAP
static void	add_other(t_data *data, char loc, int x, int y)
{
	char	*img;

	if (loc == 'C')
		img = data->textures[1];
	else if (loc == 'E')
		img = data->textures[3];
	else
		return ;
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, img, x * TILE_SIZE, y * TILE_SIZE);
}

static void	put_enemy(t_data *data, int x, int y)
{
	int			frame;
	t_enemies	*enemy;

	frame = data->player.frame;
	enemy = data->enemies;
	while (enemy != NULL)
	{
		if (frame > 3)
			frame -= 4;
		if (enemy->x == x && enemy->y == y)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->en_textures[frame], x * TILE_SIZE, y * TILE_SIZE);
		enemy = enemy->next;
	}
}

// PUTS WALLS AND BACKGROUND - HELPER TO DRAW_MAP()
void	put_map(t_data *data, char loc, int x, int y)
{
	char		*img;
	int			frame;

	if (loc == '1')
		img = data->textures[2];
	else if (loc == 'P')
	{
		frame = data->player.frame;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player.textures[frame], (data->player.pos_x * TILE_SIZE),
			(data->player.pos_y * TILE_SIZE));
		return ;
	}
	else if (loc == 'W')
	{
		put_enemy(data, x, y);
		return ;
	}
	else
		img = data->textures[0];
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, img, x * TILE_SIZE, y * TILE_SIZE);
	add_other(data, loc, x, y);
}

// PUTS MAP ON THE CREEN
void	draw_map(t_data *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map.map_height)
	{
		x = 0;
		while (x < data->map.map_width)
		{
			put_map(data, data->map.map_data[y][x], x, y);
			x++;
		}
		y++;
	}
}
