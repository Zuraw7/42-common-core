/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:48:21 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 16:07:53 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// CLEARS ALL ALLOCATED MEMMORY
void	do_destroy(t_data *data)
{
	int	j;

	j = 0;
	free_map_data(data);
	while (j < 4 && data->textures[j] && data->en_textures[j])
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[j]);
		mlx_destroy_image(data->mlx_ptr, data->en_textures[j]);
		j++;
	}
	j = 0;
	while (j < 8 && data->player.textures[j])
	{
		mlx_destroy_image(data->mlx_ptr, data->player.textures[j]);
		j++;
	}
	free_all_enemies(data);
	cleanup_get_next_line(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

// closes window on "X" button
int	close_window(t_data *data)
{
	do_destroy(data);
	exit(0);
	return (0);
}

void	close_window_hook(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 1L << 2, close_window, data);
}
