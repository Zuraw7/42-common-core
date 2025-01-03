/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:52 by rkobelie          #+#    #+#             */
/*   Updated: 2024/12/16 09:14:20 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(const char *cmd)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	exec_path[4242];
	int		i;
	int		j;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path = ft_strdup(path_env);
	dir = ft_strtok(path, ':');
	while (dir)
	{
		i = 0;
		while (dir[i])
		{
			exec_path[i] = dir[i];
			i++;
		}
		exec_path[i++] = '/';
		j = 0;
		while (cmd[j])
			exec_path[i++] = cmd[j++];
		exec_path[i] = '\0';
		if (access(exec_path, X_OK) == 0)
		{
			free(path);
			return (ft_strdup(exec_path));
		}
		dir = ft_strtok(NULL, ':');
	}
	free(path);
	return (NULL);
}