/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_winnable_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:01:55 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:18:59 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// FINDS PLAYER X AND Y
static void	find_player_loc(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.map_height)
	{
		x = 0;
		while (x < data->map.map_width)
		{
			if (map[y][x] == 'P')
			{
				data->player.pos_x = x;
				data->player.pos_y = y;
			}
			x++;
		}
		y++;
	}
}

// SETS FIRST NODE IN QUEUE LINKED LIST
t_queue	*set_queue_start(t_queue **queue, t_data *data, char **map)
{
	find_player_loc(data, map);
	*queue = malloc(sizeof(t_queue));
	if (!(*queue))
	{
		perror("Failed to set queue");
		return (0);
	}
	(*queue)->x = data->player.pos_x;
	(*queue)->y = data->player.pos_y;
	(*queue)->c = 'P';
	(*queue)->next = NULL;
	return (*queue);
}

// ADDS NEW NODE AT THE END OF QUEUE
t_queue	*add_to_queue(t_data *data, int x, int y, char **map)
{
	t_queue	*expand_queue;
	t_queue	*new_node;

	new_node = malloc(sizeof(t_queue));
	if (!new_node)
	{
		perror("Failed to add to queue");
		return (0);
	}
	new_node->x = x;
	new_node->y = y;
	new_node->c = map[y][x];
	new_node->next = NULL;
	if (data->queue == NULL)
		data->queue = new_node;
	else
	{
		expand_queue = data->queue;
		while (expand_queue->next != NULL)
			expand_queue = expand_queue->next;
		expand_queue->next = new_node;
	}
	return (data->queue);
}

// FREES QUEUE AND HELPER MAP
void	free_q_and_map(t_data *data, char **map)
{
	t_queue	*current;
	t_queue	*next_node;
	int		i;
	int		height;

	height = data->map.map_height;
	current = data->queue;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	data->queue = NULL;
	if (map)
	{
		i = 0;
		while (i < height)
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}
