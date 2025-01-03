/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:17:05 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/23 10:24:47 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_export(t_exec *exec, t_data *data)
{
	int	i;
	int	j;

	if (!exec->args[1])
		print_sorted_array(exec->envp);
	else
	{
		i = 1;
		j = 1;
		while (exec->args[i])
		{
			if (!is_valid(exec->args[i]))
			{
				fprintf(stderr, "export: `%s': not a valid identifier\n",
					exec->args[i]);
				return (1);
			}
			update_envp(data, exec, &j);
			i++;
		}
	}
	return (0);
}
