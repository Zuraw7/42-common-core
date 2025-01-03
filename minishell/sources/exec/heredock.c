/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:30:32 by rkobelie          #+#    #+#             */
/*   Updated: 2024/12/23 02:56:20 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_heredoc(const char *delimiter)
{
	int		tmp_fd;
	ssize_t	read_bytes;
	ssize_t	written_bytes;
	char	buffer[4096];

	tmp_fd = open("heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("open");
		return (-1);
	}
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		read_bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (read_bytes < 0)
		{
			perror("read");
			close(tmp_fd);
			return (-1);
		}
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0
			&& buffer[ft_strlen(delimiter)] == '\n')
			break ;
		written_bytes = write(tmp_fd, buffer, read_bytes);
		if (written_bytes != read_bytes)
		{
			perror("write");
			close(tmp_fd);
			return (-1);
		}
	}
	close(tmp_fd);
	return (open("heredoc_tmp", O_RDONLY));
}
