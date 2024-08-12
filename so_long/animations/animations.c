/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:58:52 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 17:03:07 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	enemy_animation(t_data *data, int frame)
{
	t_enemies	*enemy;

	enemy = data->enemies;
	while (enemy != NULL)
	{
		if (frame > 3)
			frame -= 4;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->en_textures[frame], (enemy->x * TILE_SIZE),
			(enemy->y * TILE_SIZE));
		enemy = enemy->next;
	}
}

int	animation(t_data *data)
{
	int			frame;

	data->player.frame = (data->player.frame + 1) % data->player.tot_frames;
	frame = data->player.frame;
	if (data->map.exit_x == data->player.pos_x
		&& data->map.exit_y == data->player.pos_y)
		frame += 4;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player.textures[frame], (data->player.pos_x * TILE_SIZE),
		(data->player.pos_y * TILE_SIZE));
	if (data->enemies)
		enemy_animation(data, frame);
	put_stats(data);
	usleep(100000);
	return (0);
}
