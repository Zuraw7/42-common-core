/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkobelie <rkobelie@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:46:37 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/24 14:06:59 by rkobelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exit(void)
{
	perror("Error");
	exit(1);
}

void	exit_clear(t_data *data)
{
	rl_clear_history();
	if (data->parsing)
	{
		clear_parsing(data->parsing);
		free(data->parsing);
		data->parsing = NULL;
	}
	if (data->exec->args != NULL && data->exec->args)
	{
		clear_exec(data->exec);
	}
	free_data_envp(data);
}

static void	free_env_var(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->env_var_count)
	{
		free(token->env_var[i]);
		i++;
	}
	free(token->env_var);
	token->env_var = NULL;
}

void	free_tokens(t_parse *parsing)
{
	int	i;

	i = 0;
	while (parsing->tokens[i])
	{
		free_env_var(parsing->tokens[i]);
		if (parsing->tokens[i]->proc_text)
			free(parsing->tokens[i]->proc_text);
		parsing->tokens[i]->envp = NULL;
		free(parsing->tokens[i]);
		i++;
	}
	free(parsing->tokens);
}

void	free_words(t_parse *parsing)
{
	int	i;

	i = 0;
	while (parsing->words[i])
	{
		free(parsing->words[i]);
		i++;
	}
	free(parsing->words);
}
