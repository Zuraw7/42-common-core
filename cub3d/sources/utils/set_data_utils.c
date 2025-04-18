/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:04:07 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 18:04:32 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_mlx	*set_mlx(t_data *data)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
	{
		printf("Error: mlx allocation failed\n");
		exit(1);
	}
	mlx->last_time = 0;
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->data = data;
	return (mlx);
}

t_map	*set_map(t_data *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		printf("Error: map allocation failed\n");
		exit(1);
	}
	map->hold_cf_color = NULL;
	map->nesw_textures = NULL;
	map->file = NULL;
	map->height = 0;
	map->width = 0;
	map->map = NULL;
	map->queue = NULL;
	map->data = data;
	return (map);
}
