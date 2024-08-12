/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:28:15 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:17:12 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
// COUNTS COLLECTIBLES AND HEIGHT OF MAP
static void	count_collectibles_and_height(int fd, t_data *data)
{
	char	*line;
	int		i;

	line = get_nl(fd, &(data->gnl));
	while (line != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == 'C')
				data->to_collect++;
			i++;
		}
		free(line);
		data->map.map_height++;
		line = get_nl(fd, &(data->gnl));
	}
	close(fd);
}

// ALLOCATE MEMORY FOR MAP (Y AXIS)
static void	allocate_map_data(t_data *data)
{
	data->map.map_data = (char **)malloc(sizeof(char *)
			* (data->map.map_height + 1));
	if (data->map.map_data == NULL)
	{
		perror("Error allocating memory for map data");
		exit(1);
	}
	data->map.map_data[data->map.map_height] = NULL;
}

// SETS MAP LINES (X AXIS)
static void	read_map_lines(int fd, t_data *data)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = get_nl(fd, &(data->gnl));
	while (line != NULL)
	{
		data->map.map_data[i] = ft_strdup(line);
		if (i == 0)
			data->map.map_width = ft_strlen(line);
		j = 0;
		while (line[j++])
		{
			if (line[j] == 'E')
			{
				data->map.exit_x = j;
				data->map.exit_y = i;
			}
		}
		free(line);
		i++;
		line = get_nl(fd, &(data->gnl));
	}
	close(fd);
}

// MAIN FUNCTION TO LOAD MAP FROM FILES
void	read_map(char *filename, t_data *data)
{
	int	fd;

	data->map.map_height = 0;
	data->to_collect = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	count_collectibles_and_height(fd, data);
	allocate_map_data(data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	read_map_lines(fd, data);
}
