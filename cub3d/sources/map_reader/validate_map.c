/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:03:57 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/02 10:36:14 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**bfs_map(t_map *map);

/*
	1. zczytanie mapy tylko mapy do map->map
	2. sprawdzenie czy znaki są poprawne oraz czy nie ma luki w mapie
	3. sprawdzenie czy jest otoczona ścianami
*/
int	validate_map(t_map *map)
{
	if (copy_map(map))
		return (1);
	if (valid_map_structure(map))
		return (1);
	if (check_walls(map))
		return (1);
	return (0);
}

// zduplikowanie mapy do tmp_map, która będzie używana do sprawdzania ścian
char	**bfs_map(t_map *map)
{
	char	**tmp_map;
	int		i;

	i = 0;
	while (map->map[i])
		i++;
	tmp_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp_map)
		return (NULL);
	tmp_map[i] = NULL;
	i = -1;
	while (map->map[++i])
		tmp_map[i] = ft_strdup(map->map[i]);
	return (tmp_map);
}
