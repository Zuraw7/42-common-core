/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_and_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:47:10 by zuraw             #+#    #+#             */
/*   Updated: 2024/11/29 17:24:52 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	len_setter(char **arr, int j)
{
	size_t	len;

	len = ft_strlen(arr[j]);
	if (len < ft_strlen(arr[j + 1]))
		len = ft_strlen(arr[j + 1]);
	return (len);
}

static void	bubble_sort(char **arr, int size)
{
	int		swapped;
	char	*temp;
	size_t	len;
	int		i;
	int		j;

	i = -1;
	while (++i < size - 1)
	{
		swapped = 0;
		j = -1;
		while (++j < size - i - 1)
		{
			len = len_setter(arr, j);
			if (ft_strncmp(arr[j], arr[j + 1], len) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break ;
	}
}

void	print_sorted_array(char **envp)
{
	char	**sorted_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	sorted_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!sorted_envp)
		error_exit();
	sorted_envp[i] = NULL;
	i = 0;
	while (envp[i])
	{
		sorted_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	bubble_sort(sorted_envp, i);
	i = -1;
	while (sorted_envp[++i])
	{
		printf("declare - x %s\n", sorted_envp[i]);
		free(sorted_envp[i]);
	}
	free(sorted_envp);
}

bool	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (false);
	i++;
	while (arg[i])
	{
		if (arg[i] == '=' || arg[i] == '\0')
			return (true);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
