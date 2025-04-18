/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 00:49:04 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 18:15:21 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int		rnd(float num);
static float	new_xy(t_player *player, float dir_x,
					float dir_y, float *new_y);

void	handle_movement(t_player *player, t_keys *keys)
{
	if (keys->w)
		move_player(player, 119);
	if (keys->s)
		move_player(player, 115);
	if (keys->a)
		move_player(player, 97);
	if (keys->d)
		move_player(player, 100);
	if (keys->left)
		rotate_player(player, 65361);
	if (keys->right)
		rotate_player(player, 65363);
}

void	move_player(t_player *player, int keycode)
{
	float	new_x;
	float	new_y;
	t_map	*map;

	new_x = player->x;
	new_y = player->y;
	map = player->data->map;
	if (keycode == 119)
		new_x = new_xy(player, player->dir_x, player->dir_y, &new_y);
	else if (keycode == 115)
		new_x = new_xy(player, -player->dir_x, -player->dir_y, &new_y);
	else if (keycode == 100)
		new_x = new_xy(player, -player->dir_y, player->dir_x, &new_y);
	else if (keycode == 97)
		new_x = new_xy(player, player->dir_y, -player->dir_x, &new_y);
	if (map->map[(int)rnd(new_y - OFFSET)][(int)rnd(new_x - OFFSET)] != '1' &&
		map->map[(int)rnd(new_y - OFFSET)][(int)rnd(new_x - OFFSET)] != '1' &&
		map->map[(int)rnd(new_y - OFFSET)][(int)rnd(new_x - OFFSET)] != '1' &&
		map->map[(int)rnd(new_y - OFFSET)][(int)rnd(new_x + OFFSET)] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static int	rnd(float num)
{
	float	decimal;
	float	integer;

	integer = num;
	decimal = modff(num, &integer);
	if (decimal > 0.85)
		return (ceil(num));
	return (floor(num));
}

static float	new_xy(t_player *player, float dir_x, float dir_y, float *new_y)
{
	float	move_speed;

	move_speed = 0.03;
	*new_y = player->y + dir_y * move_speed;
	return (player->x + dir_x * move_speed);
}
