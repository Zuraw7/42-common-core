/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:00:56 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/16 14:53:37 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

static void	open_files(t_pipex *pipex)
{
	pipex->in_fd = open(pipex->in_file, O_RDONLY);
	if (pipex->in_fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	pipex->out_fd = open(pipex->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex->out_fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
}

static void	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
}

static pid_t	create_process(int in_fd, int pipe_fd[2], t_pipex *pipex, int i)
{
	pid_t	pid;

	create_pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(in_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (in_fd != pipex->in_fd)
			close(in_fd);
		execve(pipex->cmd_paths[i], pipex->cmd_args[i], pipex->envp);
		perror("Error executing command");
		error_exit(pipex);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static pid_t	create_last_process(int in_fd, t_pipex *pipex, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(in_fd, STDIN_FILENO);
		dup2(pipex->out_fd, STDOUT_FILENO);
		close(in_fd);
		close(pipex->out_fd);
		execve(pipex->cmd_paths[i], pipex->cmd_args[i], pipex->envp);
		perror("Error executing command");
		error_exit(pipex);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	run_pipe(t_pipex *pipex)
{
	int		i;
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;

	open_files(pipex);
	in_fd = pipex->in_fd;
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pid = create_process(in_fd, pipe_fd, pipex, i);
		close(pipe_fd[1]);
		if (in_fd != pipex->in_fd)
			close(in_fd);
		in_fd = pipe_fd[0];
		i++;
	}
	pid = create_last_process(in_fd, pipex, i);
	close(in_fd);
	close(pipex->out_fd);
	i = -1;
	while (++i < pipex->cmd_count)
		wait(NULL);
	if (pid > 0)
		waitpid(pid, NULL, 0);
}
