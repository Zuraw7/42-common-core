/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <astefans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:59:46 by alicja            #+#    #+#             */
/*   Updated: 2025/04/15 19:44:20 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	calc_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x);
	else
		return ((ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y);
}

static void	textures_calculations(t_ray *ray, t_ray_vars *vars)
{
	vars->wall_dist = calc_wall_dist(ray);
	vars->line_height = (int)(HEIGHT / vars->wall_dist);
	vars->draw_start = -(vars->line_height) / 2 + HEIGHT / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = vars->line_height / 2 + HEIGHT / 2;
	if (vars->draw_end >= HEIGHT)
		vars->draw_end = HEIGHT - 1;
	vars->step = 1.0 * TEX_SIZE / vars->line_height;
	vars->tex_position = (vars->draw_start - HEIGHT / 2
			+ vars->line_height / 2) * vars->step;
	if (vars->tex_position >= TEX_SIZE)
		vars->tex_position = TEX_SIZE - 1;
	vars->wallx = get_wallx(ray);
	vars->tex_x = (int)(vars->wallx / (WIDTH / TEX_SIZE));
	if (vars->tex_x < 0)
		vars->tex_x = 0;
	if (vars->tex_x >= TEX_SIZE)
		vars->tex_x = TEX_SIZE - 1;
}

static t_img	*set_texture(t_data *data)
{
	if (data->ray->side == 0)
	{
		if (data->ray->dir_x > 0)
			return (data->rend_img->walls[1]);
		else
			return (data->rend_img->walls[3]);
	}
	else
	{
		if (data->ray->dir_y > 0)
			return (data->rend_img->walls[2]);
		else
			return (data->rend_img->walls[0]);
	}
	return (NULL);
}

static void	draw_textured_column(t_data *data, t_ray_vars *vars,
	t_img *texture, int x)
{
	int	y;

	y = vars->draw_start;
	while (y < vars->draw_end)
	{
		vars->tex_y = (int)vars->tex_position;
		vars->tex_position += vars->step;
		if (vars->tex_y < 0)
			vars->tex_y = 0;
		else if (vars->tex_y >= texture->height)
			vars->tex_y = texture->height - 1;
		if (vars->tex_x < 0)
			vars->tex_x = 0;
		else if (vars->tex_x >= texture->width)
			vars->tex_x = texture->width - 1;
		vars->offset = (vars->tex_y * texture->line_length)
			+ (vars->tex_x * vars->bytes_per_pixel);
		vars->color = *(int *)(texture->addr + vars->offset);
		if (x >= 0 && x < WIDTH)
			img_pixel_put(data->rend_img->rays, x, y, vars->color);
		y++;
	}
}

int	raycaster(t_data *data)
{
	t_ray_vars	*vars;
	t_img		*texture;
	int			x;

	vars = malloc(sizeof(t_ray_vars));
	if (!vars)
		exit_clear(data);
	x = -1;
	draw_ceiling_and_floor(data);
	while (++x < WIDTH)
	{
		if (init_ray(data->ray, data, x))
			return (1);
		calculate_step(data->ray, data->player->x, data->player->y);
		cast_ray(data, data->ray);
		if (data->ray->hit == 0)
			continue ;
		perp_wall_dist(data->ray);
		textures_calculations(data->ray, vars);
		texture = set_texture(data);
		vars->bytes_per_pixel = texture->bits_per_pixel / 8;
		draw_textured_column(data, vars, texture, x);
	}
	free(vars);
	return (0);
}
