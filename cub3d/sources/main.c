/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:25:48 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/12 20:32:07 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(t_data *data)
{
	handle_movement(data->player, &data->keys);
	raycaster(data);
	render_scene(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	input_checker(ac, av);
	set_data(&data);
	if (process_map_file(data.map, av[1]) == 1)
		return (exit_clear(&data), 1);
	data.player->dir_x = cos(data.player->dir);
	data.player->dir_y = sin(data.player->dir);
	open_window(data.mlx);
	render_imgs(&data);
	register_events(&data);
	mlx_loop_hook(data.mlx->mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx->mlx_ptr);
	return (0);
}
