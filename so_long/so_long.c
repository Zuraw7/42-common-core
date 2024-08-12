/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:12:56 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 17:05:09 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/so_long.h"

static void	set_basic_data(t_data *data)
{
	data->player.char_height = 32;
	data->player.char_width = 128;
	data->map.files_height = TILE_SIZE;
	data->map.files_width = TILE_SIZE;
	data->player.moves = 0;
	data->player.collected = 0;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->to_collect = 0;
	data->game_on = 0;
	data->gnl.buffer = NULL;
	data->enemies = NULL;
	data->player.frame = 0;
	data->player.tot_frames = 4;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_printf("No map chosen\n"), 1);
	set_basic_data(&data);
	read_map(argv[1], &data);
	map_checker(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.map_width
			* TILE_SIZE, data.map.map_height * TILE_SIZE, "so_long");
	if (!data.win_ptr)
		return (mlx_destroy_display(data.mlx_ptr), free(data.mlx_ptr), 1);
	load_textures(&data);
	set_enemies(&data);
	draw_map(&data);
	input_handler(&data);
	mlx_loop_hook(data.mlx_ptr, animation, &data);
	close_window_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
