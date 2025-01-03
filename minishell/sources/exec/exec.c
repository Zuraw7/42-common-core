/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:20:58 by rkobelie          #+#    #+#             */
/*   Updated: 2024/12/24 14:12:33 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	char	*builtin_commands[] = {"echo", "cd", "pwd", "export", "unset",
			"env", "exit", NULL};

	for (int i = 0; builtin_commands[i]; i++)
	{
		if (cmd && ft_strncmp(cmd, builtin_commands[i],
				ft_strlen(builtin_commands[i])) == 0)
			return (1);
	}
	return (0);
}

int	execute_command(t_data *data, t_exec *command_struct)
{
	pid_t	pid;
	char	*command_path;
	int		is_builtin;
	int		saved_stdin;
	int		saved_stdout;

	is_builtin = is_builtin_command(command_struct->cmd);
	if (is_builtin && !command_struct->next)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (command_struct->in != STDIN_FILENO)
		{
			if (dup2(command_struct->in, STDIN_FILENO) == -1)
			{
				perror("dup2 (stdin)");
				return (-1);
			}
			close(command_struct->in);
		}
		if (command_struct->out != STDOUT_FILENO)
		{
			if (dup2(command_struct->out, STDOUT_FILENO) == -1)
			{
				perror("dup2 (stdout)");
				return (-1);
			}
			close(command_struct->out);
		}
		execute_builtin(data, command_struct);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (command_struct->in != STDIN_FILENO)
		{
			if (dup2(command_struct->in, STDIN_FILENO) == -1)
			{
				perror("dup2 (stdin)");
				exit(EXIT_FAILURE);
			}
			close(command_struct->in);
		}
		if (command_struct->out != STDOUT_FILENO)
		{
			if (dup2(command_struct->out, STDOUT_FILENO) == -1)
			{
				perror("dup2 (stdout)");
				exit(EXIT_FAILURE);
			}
			close(command_struct->out);
		}
		if (is_builtin)
		{
			execute_builtin(data, command_struct);
			exit(g_exit_code);
		}
		if (command_struct->cmd[0] != '/' && command_struct->cmd[0] != '.')
		{
			command_path = find_path(command_struct->cmd);
			if (!command_path)
			{
				write(STDERR_FILENO, "CMD NOT FOUND\n", 15);
				exit_clear(data);
				exit(127);
			}
			execve(command_path, command_struct->args, command_struct->envp);
			perror("execve");
			free(command_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			execve(command_struct->cmd, command_struct->args,
				command_struct->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}

int	execute_pipeline(t_data *data)

{
	int pipe_fd[2];
	int status;
	pid_t last_pid;
	t_exec *current;
	int prev_fd;

	current = data->exec;
	prev_fd = STDIN_FILENO;

	while (current)
	{
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				return (-1);
			}
			current->out = pipe_fd[1];
			current->next->in = pipe_fd[0];
		}

		last_pid = execute_command(data, current);
		if (last_pid == -1)
		{
			perror("execute_command");
			return (-1);
		}
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (current->out != STDOUT_FILENO)
			close(current->out);
		prev_fd = current->in;
		current = current->next;
	}
	while (wait(&status) > 0)
		;
	unlink("heredoc_tmp");
	return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}