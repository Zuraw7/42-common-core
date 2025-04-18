/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_copy_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:07:58 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/02 08:41:13 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	dup_map(t_map *map, int *i);

/*
	1. Dotarcie do rozpoczęcia się mapy
	2. Zduplikowanie mapy do map->map
*/
int	copy_map(t_map *map)
{
	int		i;
	char	*trimmed;

	i = -1;
	while (map->file[++i])
	{
		trimmed = ft_strtrim(map->file[i], " \t\n\v\f\r");
		if (!trimmed)
			return (1);
		if (trimmed[0] != '\0' && ft_isdigit(trimmed[0]))
		{
			if (dup_map(map, &i))
				break ;
			return (free(trimmed), 0);
		}
		free(trimmed);
	}
	if (trimmed)
		free(trimmed);
	printf("Error: No map found\n");
	return (1);
}

static int	dup_map(t_map *map, int *i)
{
	int	j;

	j = 0;
	while (map->file[(*i)] && map->file[(*i)][0] != '\0')
	{
		map->map = (char **)my_realloc(map->map,
				sizeof(char *) * (j + 1), sizeof(char *) * (j + 2));
		if (!map->map)
			return (1);
		map->map[j] = ft_strdup(map->file[(*i)]);
		if (!map->map[j])
			return (1);
		j++;
		(*i)++;
	}
	map->map[j] = NULL;
	return (0);
}
