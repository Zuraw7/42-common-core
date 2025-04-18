/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:12:58 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 22:35:08 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	if (old_size >= new_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

//	checks if character is a whitespace
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

//	checks if line is empty, returns 1 if true 0 if false
int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*make_set(char *list)
{
	char	*set;
	int		i;
	int		len;

	len = ft_strlen(list);
	set = malloc(sizeof(char) * len + 1);
	if (!set)
		return (NULL);
	i = 0;
	while (i < len)
	{
		set[i] = list[i];
		i++;
	}
	set[i] = '\0';
	return (set);
}

void	set_player_dir(t_player *player)
{
	if (player->start_dir == 'N')
		player->dir = 3 * PI / 2;
	else if (player->start_dir == 'E')
		player->dir = 0;
	else if (player->start_dir == 'S')
		player->dir = PI / 2;
	else if (player->start_dir == 'W')
		player->dir = PI;
	player->dir_x = cos(player->dir);
	player->dir_y = sin(player->dir);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}
