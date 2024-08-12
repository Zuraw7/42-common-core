/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:45:38 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 16:55:31 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	textures_error_checker(void	**textures, int len, t_data *data)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!textures[i])
		{
			ft_printf("Failed to load textures\n");
			do_destroy(data);
			exit(1);
		}
		i++;
	}
}

// CHECKS IF ALL TEXTURES ARE PROPERLY LOADED
void	check_textures(t_data *data)
{
	textures_error_checker((data->en_textures), 4, data);
	textures_error_checker((data->textures), 4, data);
	textures_error_checker((data->player.textures), 8, data);
}

// FREES ALLOCATED MEMORY
void	free_map_data(t_data *data)
{
	int	i;

	if (data->map.map_data == NULL)
		return ;
	i = 0;
	while (data->map.map_data[i])
	{
		free(data->map.map_data[i]);
		i++;
	}
	free(data->map.map_data);
}
