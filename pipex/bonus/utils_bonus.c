/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:50:52 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 14:52:50 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

void	set_basic_data(t_pipex *pipex, char **envp)
{
	pipex->cmd_args = NULL;
	pipex->cmd_paths = NULL;
	pipex->here_doc = false;
	pipex->envp = envp;
}

void	run_pipex(t_pipex *pipex)
{
	find_commands_path(pipex);
	run_pipe(pipex);
	free_cmd(pipex);
}

void	error_exit(t_pipex *pipex)
{
	if (pipex->args != NULL)
		free(pipex->args);
	free_cmd(pipex);
	unlink(pipex->in_file);
}
