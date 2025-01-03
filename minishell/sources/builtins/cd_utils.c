/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:41:08 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/26 12:42:19 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_dir(char *temp_path)
{
	if (chdir(temp_path) == -1)
	{
		perror("cd");
		free(temp_path);
		return (1);
	}
	return (0);
}

int	is_correct(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->args[i])
		i++;
	if (i > 3)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	return (0);
}
