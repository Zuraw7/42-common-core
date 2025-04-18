/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:30:30 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/03 10:51:25 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	trim_values(t_map *map);
static void	free_used_values(t_map *map);

/*
	1. zczytanie pliku z mapą do map->file
	2. sprawdzenie poprawności pobranych informacji
	3. sprawdzenie poprawności mapy
	4. zmienić ścieżki na takie bez whitespaców oraz zwolnić pamięć
*/
int	process_map_file(t_map *map, char *file)
{
	map->file = read_map(file);
	if (!map->file)
		return (printf("%s", READ_ERROR), 1);
	if (validate_map_config(map))
	{
		printf("%s", VAL_CONFIG_ERROR);
		free_used_values(map);
		return (1);
	}
	if (validate_map(map))
	{
		printf("%s", VAL_ERROR);
		free_used_values(map);
		return (1);
	}
	trim_values(map);
	return (0);
}

static void	trim_values(t_map *map)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (map->nesw_textures[i])
	{
		trimmed = ft_strtrim(map->nesw_textures[i], " \t\r\n\v\f");
		free(map->nesw_textures[i]);
		map->nesw_textures[i] = trimmed;
		i++;
	}
	free_used_values(map);
}

static void	free_used_values(t_map *map)
{
	free_cf_color(map);
	free_double_arr(map->file);
}
