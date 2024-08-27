/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:36:49 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 11:02:49 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static void	cmd_reader(t_pipex *pipex, char **argv, int argc)
{
	char	**tmp;
	int		i;

	pipex->out_file = argv[argc - 1];
	pipex->cmd_count = argc - 3;
	pipex->cmd_args = (char ***)malloc(sizeof(char **)
			* (pipex->cmd_count + 1));
	if (!pipex->cmd_args)
		exit (1);
	pipex->cmd_args[pipex->cmd_count] = NULL;
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (ft_strchr(argv[i + 2], ' ') != NULL)
			tmp = ft_split(argv[i + 2], ' ');
		else
		{
			tmp = (char **)malloc(sizeof(char *) * 2);
			if (!tmp)
				exit (1);
			tmp[0] = ft_strdup(argv[i + 2]);
			tmp[1] = NULL;
		}
		pipex->cmd_args[i] = tmp;
	}
}

void	input_reader(t_pipex *pipex, char **argv, int argc)
{
	if (access(argv[1], R_OK) != -1)
		pipex->in_file = argv[1];
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	cmd_reader(pipex, argv, argc);
}

void	free_cmd(t_pipex *pipex)
{
	int	i;
	int	j;

	if (pipex->cmd_args != NULL)
	{
		i = -1;
		while (pipex->cmd_args[++i] != NULL)
		{
			j = -1;
			while (pipex->cmd_args[i][++j] != NULL)
				free(pipex->cmd_args[i][j]);
			free(pipex->cmd_args[i]);
		}
		free(pipex->cmd_args);
	}
	if (pipex->cmd_paths != NULL)
	{
		i = -1;
		while (pipex->cmd_paths[++i])
			free(pipex->cmd_paths[i]);
		free(pipex->cmd_paths);
	}
}
