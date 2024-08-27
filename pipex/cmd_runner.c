/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:00:56 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 11:17:58 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static void	execute_first(t_pipex *pipex, int pipe_fd[])
{
	pipex->in_fd = open(pipex->in_file, O_RDONLY, 0644);
	if (pipex->in_fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipex->in_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (execve(pipex->cmd_paths[0], pipex->cmd_args[0], pipex->envp) == -1)
	{
		perror("zsh");
		exit(EXIT_FAILURE);
	}
}

static void	execute_second(t_pipex *pipex, int pipe_fd[])
{
	pipex->out_fd = open(pipex->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(pipex->out_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (execve(pipex->cmd_paths[1], pipex->cmd_args[1], pipex->envp) == -1)
	{
		perror("zsh");
		exit(EXIT_FAILURE);
	}
}

static void	run_cmd(t_pipex *pipex, int pipe_fd[], void (*f)(t_pipex*, int[]))
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		f(pipex, pipe_fd);
}

void	run_pipe(t_pipex *pipex)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	run_cmd(pipex, pipe_fd, execute_first);
	run_cmd(pipex, pipe_fd, execute_second);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}
