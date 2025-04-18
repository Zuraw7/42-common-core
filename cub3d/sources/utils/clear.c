/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:02:25 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 22:42:06 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clear_rend_walls(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->rend_img->walls[i])
		{
			if (data->rend_img->walls[i]->img_ptr)
				mlx_destroy_image(data->mlx->mlx_ptr,
					data->rend_img->walls[i]->img_ptr);
			free(data->rend_img->walls[i]);
		}
	}
}

static void	clear_rend_ing(t_data *data)
{
	if (data->rend_img->minimap)
	{
		if (data->rend_img->minimap->img_ptr)
			mlx_destroy_image(data->mlx->mlx_ptr,
				data->rend_img->minimap->img_ptr);
		free(data->rend_img->minimap);
	}
	if (data->rend_img->player_mm)
	{
		if (data->rend_img->player_mm->img_ptr)
			mlx_destroy_image(data->mlx->mlx_ptr,
				data->rend_img->player_mm->img_ptr);
		free(data->rend_img->player_mm);
	}
	if (data->rend_img->rays)
	{
		if (data->rend_img->rays->img_ptr)
			mlx_destroy_image(data->mlx->mlx_ptr,
				data->rend_img->rays->img_ptr);
		free(data->rend_img->rays);
	}
	clear_rend_walls(data);
	free(data->rend_img);
}

void	exit_clear(t_data *data)
{
	if (data->map)
		free_map(data->map);
	if (data->player)
		free(data->player);
	if (data->rend_img)
		clear_rend_ing(data);
	if (data->ray)
		free(data->ray);
	if (data->mlx->win_ptr)
		mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
	if (data->mlx->mlx_ptr)
	{
		mlx_destroy_display(data->mlx->mlx_ptr);
		free(data->mlx->mlx_ptr);
	}
	if (data->mlx)
		free(data->mlx);
	exit(0);
}

void	free_double_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	clear_queue(t_bfs *queue)
{
	t_bfs	*tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
}
