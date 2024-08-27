/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:31:16 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/22 20:13:32 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.args = NULL;
	set_basic_data(&pipex, envp);
	if (argc > 5 && ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (argc < 6)
			return (ft_printf("Not enough args\n"), 1);
		here_doc(argv[2]);
		pipex.args = set_args(argv, argc);
		input_reader(&pipex, pipex.args, argc - 1);
		pipex.here_doc = true;
	}
	else
	{
		if (argc < 5)
			return (ft_printf("Not enough args\n"), 1);
		input_reader(&pipex, argv, argc);
	}
	run_pipex(&pipex);
	if (pipex.here_doc == true)
		return (unlink(pipex.in_file), free(pipex.args), 0);
	return (0);
}
