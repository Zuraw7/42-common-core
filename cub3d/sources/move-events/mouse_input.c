/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:38:17 by alicja            #+#    #+#             */
/*   Updated: 2025/04/13 18:31:22 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*obrót wektora za pomocą wzoru obrotu macierzy w 2D*/
static void	calculate_rot_dir(t_data *data, int delta_x)
{
	double	rot_speed;
	float	old_dir_x;
	float	old_plane_x;

	rot_speed = delta_x * SENSITIVITY;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cos(rot_speed) - \
		data->player->dir_y * sin(rot_speed);
	data->player->dir_y = old_dir_x * sin(rot_speed) + \
		data->player->dir_y * cos(rot_speed);
	data->player->plane_x = data->player->plane_x * cos(rot_speed) - \
		data->player->plane_y * sin(rot_speed);
	data->player->plane_y = old_plane_x * sin(rot_speed) + \
		data->player->plane_y * cos(rot_speed);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	mid_x;
	int	mid_y;
	int	delta_x;

	mid_x = WIDTH / 2;
	mid_y = HEIGHT / 2;
	delta_x = x - mid_x;
	if (delta_x != 0 && data->keys.mouse)
		calculate_rot_dir(data, delta_x);
	mlx_mouse_move(data->mlx->mlx_ptr, data->mlx->win_ptr, mid_x, mid_y);
	(void)y;
	return (0);
}
