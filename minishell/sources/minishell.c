/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:31 by pzurawic          #+#    #+#             */
/*   Updated: 2024/12/27 16:22:36 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

// Do odpalenia bez leaków readline:
/*
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
		--suppressions=readline.supp ./minishell
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	g_exit_code = 0;
	set_data(&data, envp);
	while (input_reader(&data) == true)
	{
		if (data.parsing->input == NULL)
			continue ;
		data.exec = alloc_exec();
		parsing(&data);
		execute_pipeline(&data);
		if (data.exec->args)
		{
			clear_exec(data.exec);
		}
		clear_parsing(data.parsing);
	}
	exit_clear(&data);
	return (0);
}
