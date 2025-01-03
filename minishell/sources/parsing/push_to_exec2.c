/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:29:18 by rkobelie          #+#    #+#             */
/*   Updated: 2024/12/23 18:32:13 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_token(t_exec **exec, t_parse *parsing, int *i, int *j)
{
	if (parsing->tokens[*i]->token == OPERATOR)
	{
		handle_operator(exec, parsing, i);
		*j = 0;
	}
	else if ((*exec)->cmd == NULL)
	{
		handle_command(exec, parsing, *i);
	}
	else
	{
		(*j)++;
		(*exec)->args[*j] = ft_strdup(parsing->tokens[*i]->proc_text);
	}
}

static void	set_exec(t_exec *exec, t_parse *parsing)
{
	t_exec	*exec_tmp;

	int i, j;
	i = 0, j = 0;
	exec_tmp = exec;
	while (parsing->tokens[i])
	{
		if (!exec->envp)
			exec->envp = parsing->tokens[i]->envp;
		process_token(&exec, parsing, &i, &j);
		if (parsing->tokens[i + 1] && parsing->tokens[i + 1]->token == OPERATOR)
		{
			if (!exec->cmd && !exec->operator)
			{
				exec->next = alloc_exec();
				exec->next->prev = exec;
				exec = exec->next;
			}
		}
		i++;
	}
	exec->next = NULL;
	exec = exec_tmp;
}

void	push_to_exec(t_parse *parsing, t_exec *exec)
{
	t_exec	*check_exec;
	t_exec	*prev_exec;

	set_exec(exec, parsing);
	check_exec = exec;
	prev_exec = NULL;
	while (check_exec != NULL)
	{
		if (check_exec->next == NULL && check_exec->cmd == NULL
			&& prev_exec != NULL && prev_exec->token == OPERATOR)
		{
			printf("%s", CMD_ERROR);
			error_exit();
		}
		prev_exec = check_exec;
		check_exec = check_exec->next;
	}
}
