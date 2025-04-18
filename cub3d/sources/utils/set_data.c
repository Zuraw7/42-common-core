/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:05:33 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 22:01:46 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_player		*set_player(t_data *data);
static t_rend_img	*set_rend_img(t_data *data);
static t_ray		*set_ray(t_data *data);

void	set_data(t_data *data)
{
	data->mlx = set_mlx(data);
	data->map = set_map(data);
	data->player = set_player(data);
	data->rend_img = set_rend_img(data);
	data->ray = set_ray(data);
	data->keys.w = false;
	data->keys.s = false;
	data->keys.a = false;
	data->keys.d = false;
	data->keys.left = false;
	data->keys.right = false;
	data->keys.mouse = true;
}

static t_player	*set_player(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		printf("Error: player allocation failed\n");
		exit(1);
	}
	player->data = data;
	return (player);
}

static t_rend_img	*set_rend_img(t_data *data)
{
	t_rend_img	*rend_img;
	int			i;

	rend_img = malloc(sizeof(t_rend_img));
	if (!rend_img)
	{
		printf("Error: rend_img allocation failed\n");
		exit(1);
	}
	rend_img->minimap = NULL;
	rend_img->player_mm = NULL;
	rend_img->rays = NULL;
	i = -1;
	while (++i < 4)
		rend_img->walls[i] = NULL;
	rend_img->data = data;
	return (rend_img);
}

static t_ray	*set_ray(t_data *data)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		printf("Error: ray allocation failed\n");
		exit(1);
	}
	ray->dir_x = data->player->dir_x;
	ray->dir_y = data->player->dir_y;
	ray->data = data;
	return (ray);
}
