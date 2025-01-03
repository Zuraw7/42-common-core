/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:26:45 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/01 00:02:22 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Pobieranie wartości zmiennej środowiskowej
char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	size_t	len;

	len = strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

// Zliczanie ilości zmiennych środowiskowych
int	env_var_count(t_token *token)
{
	int		count;
	int		i;
	char	quot_mark;

	quot_mark = 0;
	count = 0;
	i = -1;
	while (token->text[++i])
	{
		if (quot_mark == 0 && (token->text[i] == '\'' || token->text[i] == '"'))
		{
			quot_mark = token->text[i];
			if (quot_mark == '\'')
			{
				i += skip_squot(&token->text[i]) + 1;
				quot_mark = 0;
				if (token->text[i] == '\0')
					break ;
			}
		}
		if (token->text[i] == '$')
			count++;
	}
	return (count);
}

// Ustawia wartość zmiennej środowiskowej
void	get_env_var(t_token *token, int *i, int *j, char *value)
{
	int		len;
	char	*var_name;

	len = 0;
	while (ft_isalnum(token->text[*i + len]) || token->text[*i + len] == '_')
		len++;
	var_name = ft_substr(token->text, *i, len);
	value = get_env_value(var_name, token->envp);
	if (value)
		token->env_var[(*j)++] = ft_strdup(value);
	else
		token->env_var[(*j)++] = ft_strdup("");
	free(var_name);
	*i += len;
}

// Alokuje pamięć dla zmiennych środowiskowych i inicjalizuje wskaźniki na NULL
void	alloc_env_var(t_token *token)
{
	int	i;

	token->env_var = (char **)malloc(sizeof(char *)
			* (token->env_var_count + 1));
	if (!token->env_var)
		error_exit();
	i = -1;
	while (++i < token->env_var_count)
		token->env_var[i] = NULL;
}
