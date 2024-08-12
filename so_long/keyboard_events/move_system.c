/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:06:59 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 16:26:46 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// PUTS INFO THAT PLAYER WON IF HE HAS COLLECTED ALL AND IS ON EXIT
static void	put_win_string(t_data *data)
{
	int	color;
	int	mid_x;
	int	mid_y;

	color = 0x00FFFFFF;
	mid_x = (data->map.map_width * TILE_SIZE) / 2 - 64;
	mid_y = (data->map.map_height * TILE_SIZE) / 2;
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x, mid_y, color, "You won! Press ESC to leave");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x + 1, mid_y, color, "You won! Press ESC to leave");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x, mid_y + 1, color, "You won! Press ESC to leave");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x + 1, mid_y + 1, color, "You won! Press ESC to leave");
}

// PUTS STRING ON SCREEN IF ON EXIT AND COLLECTIBLES ARE LEFT ON MAP
static void	put_collect_string(t_data *data)
{
	int	color;
	int	mid_x;
	int	mid_y;

	color = 0x00FFFFFF;
	mid_x = (data->map.map_width * TILE_SIZE) / 2 - 32;
	mid_y = (data->map.map_height * TILE_SIZE) / 2;
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x, mid_y, color, "Collect everything!");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x + 1, mid_y, color, "Collect everything!");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x, mid_y + 1, color, "Collect everything!");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		mid_x + 1, mid_y + 1, color, "Collect everything!");
}

// CHECKS IF PLAYERS FINISHED GAME (COLLECTED ALL COLLECTIBLES AND IS ON EXIT)
static void	check_exit(int keysym, t_data *data)
{
	if (data->player.pos_x == data->map.exit_x
		&& data->player.pos_y == data->map.exit_y)
	{
		if (data->player.collected == data->to_collect)
		{
			data->game_on = 1;
			put_win_string(data);
			if (keysym == 65293)
			{
				do_destroy(data);
				exit(0);
			}
		}
		else
			put_collect_string(data);
	}
}

// MOVES PLAYER TO NEW POS, CHECKS IF EXIT OR COLLECTIBLE TO HANDLE EVENTS
static void	change_pos(int keysym, t_data *data, int new_x, int new_y)
{
	if (data->player.pos_y == data->map.exit_y
		&& data->player.pos_x == data->map.exit_x)
		data->map.map_data[data->player.pos_y][data->player.pos_x] = 'E';
	else
		data->map.map_data[data->player.pos_y][data->player.pos_x] = '0';
	if (data->map.map_data[new_y][new_x] == 'C')
		data->player.collected++;
	data->player.pos_x = new_x;
	data->player.pos_y = new_y;
	data->map.map_data[data->player.pos_y][data->player.pos_x] = 'P';
	move_towards_player(data);
	draw_map(data);
	if (keysym != 65293)
		data->player.moves++;
	check_exit(keysym, data);
	check_if_lose(keysym, data);
}

// BASE FUNCTION, SETS NEX POSITION FOR PLAYER
int	wasd_move(int keysym, t_data *data)
{
	int	new_x;
	int	new_y;

	if (data->game_on == 1)
		return (0);
	new_x = data->player.pos_x;
	new_y = data->player.pos_y;
	if (keysym == XK_w)
		new_y--;
	else if (keysym == XK_s)
		new_y++;
	else if (keysym == XK_a)
		new_x--;
	else if (keysym == XK_d)
		new_x++;
	if (data->map.map_data[new_y][new_x] != '1')
		change_pos(keysym, data, new_x, new_y);
	put_stats(data);
	return (0);
}
