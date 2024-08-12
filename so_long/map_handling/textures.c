/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:37:16 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 16:57:42 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	load_enemy_animations(t_data *data)
{
	data->en_textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/enemy/0.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->en_textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/enemy/1.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->en_textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/enemy/2.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->en_textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/enemy/3.xpm", &(data->player.char_width),
			&(data->player.char_height));
}

static void	load_player_animations(t_data *data)
{
	data->player.textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/0.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/1.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/2.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/3.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/4.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/5.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/6.xpm", &(data->player.char_width),
			&(data->player.char_height));
	data->player.textures[7] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/animations/hero/7.xpm", &(data->player.char_width),
			&(data->player.char_height));
}

// LOADS TEXTURES
void	load_textures(t_data *data)
{
	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/temporary/empty_space.xpm", &(data->map.files_width),
			&(data->map.files_height));
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/temporary/collectibles_transparent.xpm",
			&(data->map.files_width), &(data->map.files_height));
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/temporary/walls_transparent.xpm", &(data->map.files_width),
			&(data->map.files_height));
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./img/temporary/exit.xpm", &(data->map.files_width),
			&(data->map.files_height));
	load_player_animations(data);
	load_enemy_animations(data);
	check_textures(data);
}
