/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:39:14 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 13:40:09 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

void	here_doc(char *limiter)
{
	int		temp_fd;
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE];
	int		lim_len;

	lim_len = ft_strlen(limiter);
	temp_fd = open ("temp_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (temp_fd < 0)
	{
		perror("Error opening temporary file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ft_printf("here_doc> ");
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (ft_strncmp(buffer, limiter, lim_len) == 0)
			break ;
		write(temp_fd, buffer, bytes_read);
	}
	close(temp_fd);
}

char	**set_args(char **argv, int argc)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * argc - 1);
	args[0] = argv[0];
	args[1] = "temp_file.txt";
	i = 3;
	while (argv[i])
	{
		args[i - 1] = argv[i];
		i++;
	}
	return (args);
}
