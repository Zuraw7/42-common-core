/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:05:02 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:17:44 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// CHECKS IF MAP IS CORRECT
void	map_checker(t_data *data)
{
	is_rectangle(data);
	check_walls(data);
	check_if_playable(data);
	check_if_winnable(data);
}

// LEAVES PROGRAM IF MAP HAS AN ERROR
void	map_invalid_error(t_data *data)
{
	ft_printf("Error\n");
	free_map_data(data);
	cleanup_get_next_line(data);
	exit(1);
}

// CHECKS IF MAP IS RECTANGLE
void	is_rectangle(t_data *data)
{
	int		i;
	size_t	line_len;
	char	**map;

	map = data->map.map_data;
	line_len = 0;
	i = 0;
	while (map[i])
	{
		if (i > 0)
			if (line_len != ft_strlen(map[i]))
				map_invalid_error(data);
		line_len = ft_strlen(map[i]);
		i++;
	}
}

// CHECKS IF MAP IS SURROUNDED BY WALLS
void	check_walls(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	map = data->map.map_data;
	i = 0;
	while (map[i])
	{
		j = 0;
		if (i == 0 || i == data->map.map_height - 1)
		{
			while (map[i][j])
			{
				if (map[i][j] != '1')
					map_invalid_error(data);
				j++;
			}
		}
		else
			if (map[i][0] != '1'
				|| map[i][data->map.map_width - 1] != '1')
				map_invalid_error(data);
		i++;
	}
}

// CHECKS IF THERE IS 1 EXIT, 1 STARTING POSITION
// AND AT LEAST 1 COLLECTIBLE
void	check_if_playable(t_data *data)
{
	int		c_exit;
	int		c_player_pos;
	char	**map;
	int		i;
	int		j;

	map = data->map.map_data;
	c_exit = 0;
	c_player_pos = 0;
	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				c_exit++;
			if (map[i][j] == 'P')
				c_player_pos++;
			j++;
		}
		i++;
	}
	if (data->to_collect < 1 || c_exit != 1 || c_player_pos != 1)
		map_invalid_error(data);
}
