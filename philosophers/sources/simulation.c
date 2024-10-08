/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:23 by pzurawic          #+#    #+#             */
/*   Updated: 2024/10/09 00:42:39 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	synchro_routine(t_philo *philo)
{
	if (philo->data->nb_of_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(100);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

static bool	safe_check(t_data *data)
{
	pthread_mutex_lock(&data->write_lock);
	if (data->sim_status == true)
	{
		pthread_mutex_unlock(&data->write_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->write_lock);
	return (false);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchro_routine(philo);
	while (safe_check(philo->data))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, false);
	}
	return (NULL);
}

void	run_simulation(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->nb_of_philo)
	{
		data->philo[i].last_meal_time = data->start_time;
		if (pthread_create(&data->tid[i], NULL, routine, &data->philo[i]) != 0)
		{
			printf("%s", CREATE_FAIL);
			exit (1);
		}
	}
	while (safe_check(data))
	{
		i = -1;
		while (++i < data->nb_of_philo)
		{
			pthread_mutex_lock(&data->philo[i].meal_update);
			if (get_time() - data->philo[i].last_meal_time >= data->time_to_die)
				write_msg(&data->philo[i], 'd');
			pthread_mutex_unlock(&data->philo[i].meal_update);
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
