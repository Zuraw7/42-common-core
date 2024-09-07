/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:58:41 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/07 13:27:20 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_msg(t_philo *philo, char c)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	if (philo->data->sim_status == true)
	{
		if (c == 's')
			printf("%lu %d is sleeping\n", time, philo->id);
		else if (c == 't')
			printf("%lu %d is thinking\n", time, philo->id);
		else if (c == 'e')
			printf("%lu %d is eating\n", time, philo->id);
		else if (c == 'd')
		{
			printf("%lu %d died\n", time, philo->id);
			philo->data->sim_status = false;
		}
		else if (c == 'f')
			printf("%lu %d has taken a fork\n", time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	update_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->how_much_to_eat
		&& philo->finished_eating == false)
	{
		philo->finished_eating = true;
		philo->data->philo_finished++;
	}
	if (philo->data->philo_finished == philo->data->nb_of_philo)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		philo->data->sim_status = false;
		pthread_mutex_unlock(&philo->data->write_lock);
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
}

int	check_sim_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
	{
		write_msg(philo, 'd');
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return (1);
	}
	if (philo->data->sim_status == false)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	return (0);
}
