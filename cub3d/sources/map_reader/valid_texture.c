/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:25:54 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/05 11:03:46 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_file_ext(char *path);
static int	try_to_open(char *path);
static int	is_empty_file(int fd);

/*
	1. Tesktury
		a. czy plik istnieje? OPEN flaga O_RDONLY
			1. czy plik nie zawiera tylko samych białych znaków?
		b. czy plik ma poprawne rozszerzenie .xpm
*/
int	valid_textures(t_map *map)
{
	int	i;

	i = 0;
	while (map->nesw_textures[i])
	{
		if (try_to_open(map->nesw_textures[i]))
			return (1);
		if (check_file_ext(map->nesw_textures[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	is_empty_file(int fd)
{
	char	*buffer;
	ssize_t	bytes;
	size_t	i;

	if (fd < 0)
		return (perror("Error opening file"), 1);
	buffer = malloc(1024);
	if (!buffer)
		return (perror("Error allocating buffer"), 1);
	while (1)
	{
		bytes = read(fd, buffer, sizeof(buffer));
		if (bytes <= 0)
			break ;
		i = 0;
		while (i < (size_t)bytes)
		{
			if (!ft_isspace(buffer[i]))
				return (free(buffer), 0);
			i++;
		}
	}
	free(buffer);
	printf("Error: empty file or whitespace only\n");
	return (1);
}

static int	try_to_open(char *path)
{
	int		fd;
	char	*trimmed_path;

	trimmed_path = ft_strtrim(path, " \t\v\r\n");
	if (!trimmed_path)
	{
		perror("Error allocating memory for trimmed path");
		return (1);
	}
	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		free(trimmed_path);
		return (1);
	}
	if (is_empty_file(fd))
	{
		close(fd);
		free(trimmed_path);
		return (1);
	}
	close(fd);
	free(trimmed_path);
	return (0);
}

static int	check_file_ext(char *path)
{
	int		i;
	char	*trimmed;

	if (!path)
		return (1);
	trimmed = ft_strtrim(path, " \t\v\r\n");
	i = ft_strlen(trimmed);
	if (i < 5 || ft_strncmp(&trimmed[i - 4], ".xpm", 4))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}
