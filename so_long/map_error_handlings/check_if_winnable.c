/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_winnable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:00:45 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:17:42 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// MAKES COPY OF MAP TO CHECK IF ITS WINNABLE
char	**set_map(t_data *data)
{
	int		i;
	char	**map;
	int		height;

	height = data->map.map_height;
	map = (char **)malloc(sizeof(char *) * height);
	if (!map)
	{
		perror("Failed to allocate memory for map");
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		map[i] = ft_strdup(data->map.map_data[i]);
		i++;
	}
	return (map);
}

// CHECKS IF MOVE IS POSSIBLE, AND IS IT C OR E
void	check_and_add(t_bfs_params *params, int x, int y)
{
	if (params->map[y][x] != 'Q' && params->map[y][x] != '1')
	{
		params->data->queue = add_to_queue(params->data, x, y, params->map);
		if (params->map[y][x] == 'C')
			(*params->check_coll)--;
		else if (params->map[y][x] == 'E')
			(*params->check_exit)++;
		params->map[y][x] = 'Q';
	}
}

// Breadth-first search -- ALGORITHM TO GO THRU 2D MAP
void	bfs(t_data *data, int *check_coll, int *check_exit, char **map)
{
	t_queue			*temp;
	int				temp_x;
	int				temp_y;
	t_bfs_params	params;

	params.data = data;
	params.check_coll = check_coll;
	params.check_exit = check_exit;
	params.map = map;
	temp = data->queue;
	while (temp != NULL)
	{
		temp_x = temp->x;
		temp_y = temp->y;
		check_and_add(&params, temp_x, temp_y + 1);
		check_and_add(&params, temp_x + 1, temp_y);
		check_and_add(&params, temp_x, temp_y - 1);
		check_and_add(&params, temp_x - 1, temp_y);
		temp = temp->next;
	}
}

// MAIN FUNCTION TO CHECK IF MAP IS WINNABLE
void	check_if_winnable(t_data *data)
{
	char	**map;
	int		check_coll;
	int		check_exit;

	check_exit = 0;
	check_coll = data->to_collect;
	map = set_map(data);
	data->queue = set_queue_start(&(data->queue), data, map);
	bfs(data, &check_coll, &check_exit, map);
	free_q_and_map(data, map);
	if (check_exit == 1 && check_coll == 0)
		return ;
	else
		map_invalid_error(data);
}
