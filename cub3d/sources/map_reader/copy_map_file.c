/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:57:12 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/05 11:50:17 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**resize_map(char **map, size_t current_size);
static char	**set_null(char **map, int i);

/*
	Funkcja czytająca plik mapy
	1. Otwarcie pliku
	2. Odczytywanie linii z pliku w pętli
	3. Zapisanie linii do mapy
		a. Zwiększenie rozmiaru mapy -> resize_map
		b. Skopiowanie linii do mapy -> ft_strdup
	4. Ustawienie null na końcu mapy -> set_null
	6. Zwrócenie mapy
*/
char	**read_map(char *file)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Unable to open file\n"), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map = resize_map(map, i);
		map[i] = ft_strdup(line);
		if (!map[i])
			return (printf("Error: malloc failed\n"), NULL);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map = set_null(map, i);
	close(fd);
	return (map);
}

static char	**resize_map(char **map, size_t current_size)
{
	map = (char **)my_realloc(map, current_size * sizeof(char *),
			(current_size + 1) * sizeof(char *));
	if (!map)
		return (printf("Error: malloc failed\n"), NULL);
	map[current_size] = NULL;
	return (map);
}

static char	**set_null(char **map, int i)
{
	map = my_realloc(map, i * sizeof(char *), (i + 1) * sizeof(char *));
	if (!map)
		return (printf("Error: malloc failed\n"), NULL);
	map[i] = NULL;
	return (map);
}
