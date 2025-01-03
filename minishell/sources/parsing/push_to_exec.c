/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:54:56 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/23 21:01:24 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_parse *parsing)
{
	int	j;

	if (!parsing || !parsing->tokens)
		return (0);
	j = 0;
	while (parsing->tokens[j] && parsing->tokens[j]->token != OPERATOR)
	{
		if (!parsing->tokens[j])
			break ;
		j++;
	}
	return (j);
}

static void	alloc_args(t_exec *exec, t_parse *parsing, int i)
{
	int	arg_count;
	int	j;

	j = 1;
	arg_count = count_args(parsing);
	if (arg_count == 0)
	{
		exec->args = NULL;
		exec->cmd = NULL;
		return ;
	}
	exec->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!exec->args)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	for (int k = 0; k <= arg_count; k++)
		exec->args[k] = NULL;
	exec->cmd = ft_strdup(parsing->tokens[i]->proc_text);
	if (!exec->cmd)
	{
		perror("ft_strdup failed for cmd");
		free(exec->args);
		exit(EXIT_FAILURE);
	}
	exec->args[0] = exec->cmd;
	while (j < arg_count)
	{
		if (!parsing->tokens[i + j] || !parsing->tokens[i + j]->proc_text)
			break ;
		exec->args[j] = ft_strdup(parsing->tokens[i + j]->proc_text);
		if (!exec->args[j])
		{
			perror("ft_strdup failed for args[j]");
			for (int k = 0; k < j; k++)
				free(exec->args[k]);
			exec->args = NULL;
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

void	handle_operator(t_exec **exec, t_parse *parsing, int *i)
{
	int		fd;
	t_exec	*new_node;

	if (ft_strcmp(parsing->tokens[*i]->proc_text, ">") == 0)
	{
		fd = open(parsing->tokens[++(*i)]->proc_text,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (ft_strcmp(parsing->tokens[*i]->proc_text, ">>") == 0)
	{
		fd = open(parsing->tokens[++(*i)]->proc_text,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (ft_strcmp(parsing->tokens[*i]->proc_text, "<") == 0)
	{
		fd = open(parsing->tokens[++(*i)]->proc_text, O_RDONLY);
	}
	else if (ft_strcmp(parsing->tokens[*i]->proc_text, "<<") == 0)
	{
		fd = handle_heredoc(parsing->tokens[++(*i)]->proc_text);
		if (fd == -1)
		{
			perror("heredoc");
			return ;
		}
		(*exec)->in = fd;
	}
	else
	{
		(*exec)->operator= ft_strdup(parsing->tokens[*i]->proc_text);
		(*exec)->token = OPERATOR;
		fd = -1;
	}
	if (fd != -1)
	{
		if (ft_strcmp(parsing->tokens[*i - 1]->proc_text, "<") == 0
			|| ft_strcmp(parsing->tokens[*i - 1]->proc_text, "<<") == 0)
		{
			(*exec)->in = fd;
		}
		else
		{
			(*exec)->out = fd;
		}
	}
	else
	{
		new_node = alloc_exec();
		new_node->prev = *exec;
		(*exec)->next = new_node;
		*exec = new_node;
		(*exec)->next = NULL;
	}
}

void	handle_command(t_exec **exec, t_parse *parsing, int i)
{
	alloc_args(*exec, parsing, i);
	if ((*exec)->cmd == NULL)
	{
		(*exec)->cmd = ft_strdup(parsing->tokens[i]->proc_text);
	}
	if (parsing->tokens[i]->token == BUILTIN)
	{
		(*exec)->token = BUILTIN;
	}
}
