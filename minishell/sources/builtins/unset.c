/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:02:39 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/23 12:33:51 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_duplicate(char **args, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (ft_strncmp(args[i], args[index], ft_strlen(args[index])) == 0)
			return (true);
		i++;
	}
	return (false);
}

static int	count_envp(char **envp, char **args)
{
	int	i;
	int	j;
	int	count;
	int	len;

	i = -1;
	count = 0;
	while (args[++i])
	{
		if (!is_duplicate(args, i))
		{
			j = -1;
			len = ft_strlen(args[i]);
			while (envp[++j])
			{
				if (ft_strncmp(args[i], envp[j], len) == 0
					&& envp[j][len] == '=')
				{
					count++;
					break ;
				}
			}
		}
	}
	return (count);
}

static char	**alloc_new_envp(char **envp, int count)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i - count + 1));
	if (!new_envp)
		error_exit();
	new_envp[i - count] = NULL;
	return (new_envp);
}

static char	**set_new_envp(char **envp, char **new_envp, char **args)
{
	int	i;
	int	j;
	int	k;
	int	len;
	int	should_skip;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		should_skip = 0;
		k = -1;
		while (args[++k])
		{
			len = ft_strlen(args[k]);
			if (ft_strncmp(args[k], envp[i], len) == 0 && envp[i][len] == '=')
			{
				should_skip = 1;
				break ;
			}
		}
		if (!should_skip)
			new_envp[++j] = ft_strdup(envp[i]);
	}
	return (new_envp);
}

/*
	Funkcja:
	1. zlicza ilość podanych argumentów w ENVP
	2. alokuje nową tablicę dla nowego envp
	3. przypisuje do nowego envp wartości z envp, które nie są w args
	4. zwlania stare ENVP i przypisuje nowe envp do data->envp
	5. przypisuje nowe envp do execów
*/
int	builtin_unset(t_exec *exec, t_data *data)
{
	int		count;
	char	**new_envp;

	if (exec->args)
	{
		count = count_envp(data->envp, exec->args);
		new_envp = alloc_new_envp(data->envp, count);
		new_envp = set_new_envp(data->envp, new_envp, exec->args);
		free_data_envp(data);
		data->envp = new_envp;
		set_exec_envp(data->exec, data->envp);
	}
	return (0);
}
