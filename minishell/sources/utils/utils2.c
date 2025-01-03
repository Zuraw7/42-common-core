/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:31:36 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/23 12:32:05 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data_envp(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		free(data->envp[i]);
	free(data->envp);
	data->envp = NULL;
}
