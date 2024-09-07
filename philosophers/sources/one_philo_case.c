/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:16 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/07 13:27:14 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_lock(philo->l_fork);
	write_msg(philo, 'f');
	while (1)
	{
		if (check_sim_status(philo) == 1)
			break ;
		sleeping(philo);
		if (check_sim_status(philo) == 1)
			break ;
		thinking(philo);
	}
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	one_philo_case(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, one_philo_routine,
			&data->philo[0]) != 0)
	{
		printf("%s", CREATE_FAIL);
		exit (1);
	}
	if (pthread_join(data->tid[0], NULL) != 0)
	{
		printf("%s", JOIN_FAIL);
		exit (1);
	}
}
