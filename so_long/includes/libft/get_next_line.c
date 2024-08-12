/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:01:08 by pzurawic          #+#    #+#             */
/*   Updated: 2024/07/22 16:37:35 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlinecpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while ((i < size - 1) && (src[i] != '\0'))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\n';
		dest[i + 1] = '\0';
	}
	return (ft_strlen(src));
}

static void	fill_buffer(char **buffer, int fd)
{
	char	*temp;
	int		bytes;

	while (ft_strchr(*buffer, '\n') == NULL)
	{
		temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(temp);
			free(*buffer);
			*buffer = NULL;
			break ;
		}
		if (bytes == 0)
		{
			free(temp);
			break ;
		}
		temp[bytes] = '\0';
		*buffer = join_and_free(buffer, temp);
	}
}

static void	i_have_no_lines_left(char **line, char **buffer)
{
	*line = malloc((ft_strlen(*buffer) + 1) * sizeof(char));
	if (!(*line))
	{
		line = NULL;
		return ;
	}
	ft_strlcpy(*line, *buffer, ft_strlen(*buffer) + 1);
	free(*buffer);
	*buffer = NULL;
}

static char	*make_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	line_len;
	char	*newline_pos;

	if (buffer == NULL || *buffer == NULL)
		return (NULL);
	line = NULL;
	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos != NULL)
	{
		line_len = ft_strlen(*buffer) - ft_strlen(newline_pos) + 1;
		line = malloc((line_len + 1) * sizeof(char));
		if (!line)
			return (NULL);
		ft_strlinecpy(line, *buffer, line_len);
		temp = malloc((ft_strlen(*buffer) - line_len + 1) * sizeof(char));
		if (!temp)
			return (free(line), NULL);
		ft_strlcpy(temp, *buffer + line_len, ft_strlen(*buffer) - line_len + 1);
		return (free(*buffer), *buffer = temp, line);
	}
	i_have_no_lines_left(&line, buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	static int	flag = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (flag == 1)
	{
		buffer = malloc(1 * sizeof(char));
		*buffer = '\0';
		flag = 0;
	}
	if (!buffer)
		return (NULL);
	fill_buffer(&buffer, fd);
	line = make_line(&buffer);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main ()
// {
// 	int fd = open("plik.txt", O_RDONLY);
// 	char *line;

// 	if (fd == -1) {
// 		perror("Unable to open file");
// 		return (1);
// 	}

// 	int i = 1;
// 	while ((line = get_next_line(fd)) != NULL) {
// 			printf("%s", line);
// 			free(line);
// 			i++;
// 	}
// 	close(fd);
// 	return (0);
// }