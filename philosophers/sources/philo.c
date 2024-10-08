/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:55:11 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/05 10:30:09 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
		check_input(argc, argv, &data);
	else
		return (printf("%s", INPUT_ERROR), 1);
	init_forks_and_philos(&data);
	if (data.nb_of_philo == 1)
		one_philo_case(&data);
	else
	{
		run_simulation(&data);
		end_simulation(&data);
	}
	exit_clearly(&data);
	return (0);
}
