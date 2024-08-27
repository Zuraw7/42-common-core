/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:08:21 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 15:09:45 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

static void	free_cat(char **catalogs)
{
	int	i;

	i = 0;
	while (catalogs[i])
	{
		free(catalogs[i]);
		i++;
	}
	free(catalogs);
}

static char	*catalog_checker(char **catalogs, char *cmd)
{
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	while (catalogs[i] != NULL)
	{
		tmp_path = ft_strjoin(catalogs[i], "/");
		if (!tmp_path)
			return (free_cat(catalogs), NULL);
		path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!path)
			return (free_cat(catalogs), NULL);
		if (access(path, X_OK) == 0)
			return (free_cat(catalogs), path);
		free(path);
		i++;
	}
	return (free_cat(catalogs), NULL);
}

static char	*find_path(char *cmd, char **envp)
{
	char	*envp_path;
	char	**catalogs;
	int		i;

	envp_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (envp_path == NULL)
		return (NULL);
	catalogs = ft_split(envp_path, ':');
	i = 0;
	return (catalog_checker(catalogs, cmd));
}

void	find_commands_path(t_pipex *pipex)
{
	int	i;

	pipex->cmd_paths = (char **)malloc(sizeof(char *) * (pipex->cmd_count + 1));
	if (!pipex->cmd_paths)
	{
		perror("Error allocating memmory for command paths");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_paths[i] = find_path(pipex->cmd_args[i][0], pipex->envp);
		if (pipex->cmd_paths[i] == NULL)
		{
			ft_printf("command not found: %s\n", pipex->cmd_args[i][0]);
			pipex->cmd_paths[i] = NULL;
			pipex->cmd_paths[pipex->cmd_count] = NULL;
			error_exit(pipex);
			exit(1);
		}
		i++;
	}
	pipex->cmd_paths[pipex->cmd_count] = NULL;
}
