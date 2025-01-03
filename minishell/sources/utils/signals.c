/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:33 by pzurawic          #+#    #+#             */
/*   Updated: 2024/12/19 11:59:43 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	interactive_sigint(int signo)
{
	(void) signo;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigaction_error(int signal)
{
	if (signal == SIGINT)
		perror("sigaction SIGINT");
	else if (signal == SIGQUIT)
		perror("sigaction SIGQUIT");
	exit(EXIT_FAILURE);
}

void	interactive_mode_signals(t_data *data)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = interactive_sigint;
	if (sigemptyset(&sa_int.sa_mask) == -1)
		exit(EXIT_FAILURE);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		sigaction_error(SIGINT);
	sa_quit.sa_handler = SIG_IGN;
	if (sigemptyset(&sa_quit.sa_mask) == -1)
	{
		clear_parsing(data->parsing);
		clear_exec(data->exec);
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		sigaction_error(SIGQUIT);
}
