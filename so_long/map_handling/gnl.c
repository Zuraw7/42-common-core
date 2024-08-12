/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:39:56 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:16:59 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// I COULDN'T USE MY OLD GNL BECAUSE IT WASN'T READING SAME FILE TWICE
// SO I HAD TO REDO IT (BUFFER IN STRUCT IS TO MAKE IT EASY TO FREE)
static void	fill_buffer(t_gnl *gnl, int fd)
{
	char	*temp;
	int		bytes;

	while (!ft_strchr(gnl->buffer, '\n'))
	{
		temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!temp)
			return ;
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(temp);
			if (bytes == 0)
				break ;
			free(gnl->buffer);
			gnl->buffer = NULL;
			return ;
		}
		temp[bytes] = '\0';
		gnl->buffer = join_and_free(&(gnl->buffer), temp);
	}
}

static char	*make_line(t_gnl *gnl)
{
	char	*line;
	char	*temp;
	char	*newline_pos;

	if (!gnl->buffer || !*gnl->buffer)
		return (NULL);
	newline_pos = ft_strchr(gnl->buffer, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(gnl->buffer);
		temp = ft_strdup(newline_pos + 1);
		free(gnl->buffer);
		gnl->buffer = temp;
	}
	else
	{
		line = ft_strdup(gnl->buffer);
		free(gnl->buffer);
		gnl->buffer = NULL;
	}
	return (line);
}

char	*get_nl(int fd, t_gnl *gnl)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl->buffer)
	{
		gnl->buffer = malloc(BUFFER_SIZE + 1);
		if (!gnl->buffer)
			return (NULL);
		gnl->buffer[0] = '\0';
	}
	fill_buffer(gnl, fd);
	if (!gnl->buffer)
		return (NULL);
	line = make_line(gnl);
	return (line);
}

void	cleanup_get_next_line(t_data *data)
{
	if (data->gnl.buffer)
	{
		free(data->gnl.buffer);
		data->gnl.buffer = NULL;
	}
}
