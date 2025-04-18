/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <astefans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:30:06 by alicja            #+#    #+#             */
/*   Updated: 2025/04/15 19:48:16 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_wallx(t_ray *ray)
{
	double	wallx;

	if (ray->side == 0)
		wallx = ray->pos_y + ray->perpwalldist * ray->dir_y;
	else
		wallx = ray->pos_x + ray->perpwalldist * ray->dir_x;
	wallx -= floor(wallx);
	wallx *= (double)WIDTH;
	return (wallx);
}

void	draw_ceiling_and_floor(t_data *data)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = data->map->ceiling_color;
	while (y < HEIGHT)
	{
		x = 0;
		if (y > HEIGHT / 2)
			color = data->map->floor_color;
		while (x < WIDTH)
		{
			img_pixel_put(data->rend_img->rays, x, y, color);
			x++;
		}
		y++;
	}
}

void	perp_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perpwalldist = (ray->map_x - ray->pos_x);
		ray->perpwalldist += (1 - ray->step_x) / 2;
		ray->perpwalldist /= ray->dir_x;
	}
	else
	{
		ray->perpwalldist = (ray->map_y - ray->pos_y);
		ray->perpwalldist += (1 - ray->step_y) / 2;
		ray->perpwalldist /= ray->dir_y;
	}
}
