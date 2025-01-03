/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_env_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:23:13 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/23 10:24:07 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_exec *exec)
{
	int	i;
	int	n_flag;

	if (!exec->args[1])
	{
		printf("\n");
		return (0);
	}
	i = 1;
	n_flag = 0;
	if (exec->args[i] && ft_strncmp(exec->args[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (exec->args[i])
	{
		printf("%s", exec->args[i]);
		if (exec->args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

int	builtin_env(char **args, char **envp)
{
	int	i;

	if (args[1])
	{
		if (ft_strncmp(args[1], "", 1) != 0 && access(args[1], F_OK) == -1)
		{
			printf("env: %s: No such file or directory\n", args[1]);
			return (127);
		}
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

void	builtin_exit(t_data *data)
{
	printf("exit\n");
	exit_clear(data);
	exit(g_exit_code);
}

char	*get_current_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	return (path);
}

// Funkcja musi zmieniac $PWD na aktualną ścieżkę
int	builtin_pwd(void)
{
	char	*path;

	path = get_current_path();
	printf("%s\n", path);
	free(path);
	return (0);
}
