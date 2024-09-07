/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:23 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/07 13:27:23 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(100);
	while (philo->data->sim_status == true)
	{
		if (check_sim_status(philo) == 1)
			break ;
		eating(philo);
		if (check_sim_status(philo) == 1)
		{
			putdown_forks(philo);
			break ;
		}
		putdown_forks(philo);
		sleeping(philo);
		if (check_sim_status(philo) == 1)
			break ;
		if (philo->data->time_to_eat - philo->data->time_to_sleep != 0)
			thinking(philo);
	}
	return (NULL);
}

void	run_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_of_philo)
	{
		data->philo[i].last_meal_time = data->start_time;
		if (pthread_create(&data->tid[i], NULL, routine, &data->philo[i]) != 0)
		{
			printf("%s", CREATE_FAIL);
			exit (1);
		}
		i++;
	}
	while (data->sim_status == true)
	{
		i = 0;
		while (i < data->nb_of_philo)
		{
			if (get_time() - data->philo[i].last_meal_time >= data->time_to_die)
				write_msg(&data->philo[i], 'd');
			i++;
		}
	}
}

void	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
		{
			printf("%s", JOIN_FAIL);
			exit (1);
		}
		i++;
	}
}
