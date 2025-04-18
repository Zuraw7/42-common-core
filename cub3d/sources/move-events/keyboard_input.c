/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:01:14 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/12 11:17:25 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	if (keycode == 119)
		data->keys.w = true;
	else if (keycode == 115)
		data->keys.s = true;
	else if (keycode == 97)
		data->keys.a = true;
	else if (keycode == 100)
		data->keys.d = true;
	else if (keycode == 65361)
		data->keys.left = true;
	else if (keycode == 65363)
		data->keys.right = true;
	return (0);
}

static int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = false;
	else if (keycode == 115)
		data->keys.s = false;
	else if (keycode == 97)
		data->keys.a = false;
	else if (keycode == 100)
		data->keys.d = false;
	else if (keycode == 65361)
		data->keys.left = false;
	else if (keycode == 65363)
		data->keys.right = false;
	return (0);
}

void	register_events(t_data *data)
{
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win_ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->mlx->win_ptr, 6, 1L << 6, mouse_move, data);
}
