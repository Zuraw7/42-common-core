/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:34:22 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/27 16:24:08 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_parsing(t_parse *parsing)
{
	if (parsing->operators)
	{
		free(parsing->operators);
		parsing->operators = NULL;
	}
	if (parsing->words)
	{
		free_words(parsing);
		parsing->words = NULL;
	}
	if (parsing->tokens)
	{
		free_tokens(parsing);
		parsing->tokens = NULL;
	}
	if (parsing->input)
	{
		free(parsing->input);
		parsing->input = NULL;
	}
}

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

void	clear_exec(t_exec *exec)
{
	t_exec	*temp;

	if (!exec)
		return ;
	while (exec->prev != NULL)
		exec = exec->prev;
	while (exec)
	{
		temp = exec->next;
		if (exec->operator)
		{
			free(exec->operator);
			exec->operator = NULL;
		}
		if (exec->args && exec ->args[0])
		{
			free_args(exec->args);
			exec->args = NULL;
		}
		free(exec);
		exec = temp;
	}
}
