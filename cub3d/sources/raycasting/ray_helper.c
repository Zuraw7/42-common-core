/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <astefans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:49:19 by alicja            #+#    #+#             */
/*   Updated: 2025/04/15 19:48:08 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fix_zero_dir(double *dir)
{
	if (fabs(*dir) < 0.000001)
	{
		if (*dir < 0)
			*dir = 0.000001;
		else
			*dir = -0.000001;
	}
}

int	init_ray(t_ray *ray, t_data *data, int x)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	dir_x = data->player->dir_x;
	dir_y = data->player->dir_y;
	plane_x = data->player->plane_x;
	plane_y = data->player->plane_y;
	ray->pos_x = data->player->x;
	ray->pos_y = data->player->y;
	ray->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->dir_x = dir_x + plane_x * ray->camera_x;
	ray->dir_y = dir_y + plane_y * ray->camera_x;
	fix_zero_dir(&ray->dir_x);
	fix_zero_dir(&ray->dir_y);
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->delta_x = fabs(1.0 / ray->dir_x);
	ray->delta_y = fabs(1.0 / ray->dir_y);
	ray->hit = 0;
	return (0);
}

void	calculate_step(t_ray *ray, double pos_x, double pos_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - pos_y) * ray->delta_y;
	}
}

static void	calculate_side(t_data *data, t_ray *ray)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->map_x < 0 || ray->map_x >= data->map->width
		|| ray->map_y < 0 || ray->map_y >= data->map->height
		|| data->map->map[ray->map_y][ray->map_x] == '1')
		ray->hit = 1;
}

void	cast_ray(t_data *data, t_ray *ray)
{
	int	max_steps;

	max_steps = 1000;
	while (ray->hit == 0 && max_steps-- > 0)
		calculate_side(data, ray);
}
