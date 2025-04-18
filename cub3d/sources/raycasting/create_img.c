/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:08:28 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 22:00:06 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_img	*init_textures(t_data *data, int i, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr,
			data->map->nesw_textures[i], &width, &height);
	if (!img->img_ptr)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->width = width;
	img->height = height;
	img->data = data;
	return (img);
}

void	render_imgs(t_data *data)
{
	t_rend_img	*rend_img;
	int			i;

	rend_img = data->rend_img;
	rend_img->minimap = init_img(data, data->mlx->mlx_ptr,
			data->map->width * PX / 4, data->map->height * PX / 4);
	rend_img->player_mm = init_img(data, data->mlx->mlx_ptr, PX / 8, PX / 8);
	rend_img->rays = init_img(data, data->mlx->mlx_ptr, WIDTH, HEIGHT);
	i = -1;
	while (++i < 4)
	{
		rend_img->walls[i] = init_textures(data, i, TEX_SIZE, TEX_SIZE);
		if (!rend_img->walls[i])
			exit_clear(data);
	}
	if (!rend_img->minimap || !rend_img->player_mm)
	{
		printf("Error allocating minimap\n");
		exit_clear(data);
	}
	draw_minimap(data);
	draw_player(data->rend_img->player_mm);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile_to_minimap(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < PX / 4)
	{
		i = 0;
		while (i < PX / 4)
		{
			img_pixel_put(img, x * PX / 4 + i, y * PX / 4 + j, color);
			i++;
		}
		j++;
	}
}
