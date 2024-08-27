/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:31:16 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 11:20:58 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.cmd_args = NULL;
	pipex.cmd_paths = NULL;
	if (argc != 5)
		return (ft_printf("Not enough or too many args\n"), 1);
	pipex.envp = envp;
	input_reader(&pipex, argv, argc);
	find_commands_path(&pipex);
	run_pipe(&pipex);
	free_cmd(&pipex);
	return (0);
}
