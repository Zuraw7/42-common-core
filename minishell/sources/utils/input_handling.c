/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:28 by pzurawic          #+#    #+#             */
/*   Updated: 2024/12/19 14:17:13 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// sprawdza input i dodaje go do historii oraz do parsing->input
bool	input_reader(t_data *data)
{
	char	*input;
	char	*trimmed_input;

	interactive_mode_signals(data);
	input = readline("minishell> ");
	if (!input)
	{
		printf("exit\n");
		free(input);
		return (false);
	}
	trimmed_input = ft_strtrim(input, " \t\n\r\f\v");
	if (!trimmed_input || *trimmed_input == '\0')
	{
		free(input);
		free(trimmed_input);
		data->parsing->input = NULL;
		return (true);
	}
	add_history(input);
	data->parsing->input = input;
	free(trimmed_input);
	return (true);
}
