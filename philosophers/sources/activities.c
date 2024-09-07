/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:28 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/07 13:27:02 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	t_data	*data;
	time_t	time;

	data = philo->data;
	if (data->time_to_eat > data->time_to_sleep)
		time = data->time_to_eat - data->time_to_sleep;
	else
		time = data->time_to_sleep - data->time_to_eat;
	write_msg(philo, 't');
	usleep(time * 1000);
}

void	sleeping(t_philo *philo)
{
	write_msg(philo, 's');
	usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		write_msg(philo, 'f');
		pthread_mutex_lock(philo->l_fork);
		write_msg(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		write_msg(philo, 'f');
		pthread_mutex_lock(philo->r_fork);
		write_msg(philo, 'f');
	}
	pthread_mutex_lock(&philo->meal_update);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_update);
	write_msg(philo, 'e');
	usleep(philo->data->time_to_eat * 1000);
	if (philo->data->how_much_to_eat != -1)
		update_meals(philo);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
