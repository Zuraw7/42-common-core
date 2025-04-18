/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:15:30 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 18:23:02 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	right(t_player *player)
{
	double	rotate_speed;
	double	old_dir_x;
	double	old_plane_x;

	rotate_speed = 0.03;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rotate_speed)
		- player->dir_y * sin(rotate_speed);
	player->dir_y = old_dir_x * sin(rotate_speed)
		+ player->dir_y * cos(rotate_speed);
	player->plane_x = player->plane_x * cos(rotate_speed)
		- player->plane_y * sin(rotate_speed);
	player->plane_y = old_plane_x * sin(rotate_speed)
		+ player->plane_y * cos(rotate_speed);
	player->dir += rotate_speed;
}

static void	left(t_player *player)
{
	double	rotate_speed;
	double	old_dir_x;
	double	old_plane_x;

	rotate_speed = 0.03;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-rotate_speed)
		- player->dir_y * sin(-rotate_speed);
	player->dir_y = old_dir_x * sin(-rotate_speed)
		+ player->dir_y * cos(-rotate_speed);
	player->plane_x = player->plane_x * cos(-rotate_speed)
		- player->plane_y * sin(-rotate_speed);
	player->plane_y = old_plane_x * sin(-rotate_speed)
		+ player->plane_y * cos(-rotate_speed);
	player->dir -= rotate_speed;
}

void	rotate_player(t_player *player, int keycode)
{
	if (keycode == 65363)
		right(player);
	else if (keycode == 65361)
		left(player);
	if (player->dir < 0)
		player->dir += 2 * PI;
	if (player->dir >= 2 * PI)
		player->dir -= 2 * PI;
}
