/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:31:31 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 14:53:16 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	*in_file;
	char	*out_file;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
	char	**envp;
	bool	here_doc;
	char	**args;
}	t_pipex;

// CMD_UTILS
void	input_reader(t_pipex *pipex, char **argv, int argc);
void	free_cmd(t_pipex *pipex);

// PATH_FINDER
void	find_commands_path(t_pipex *pipex);

// CMD RUNNER
void	run_pipe(t_pipex *pipex);

// HERE_DOC
void	here_doc(char *limiter);
char	**set_args(char **argv, int argc);

// UTILS
void	set_basic_data(t_pipex *pipex, char **envp);
void	run_pipex(t_pipex *pipex);
void	error_exit(t_pipex *pipex);

#endif