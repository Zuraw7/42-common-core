/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:28 by pzurawic          #+#    #+#             */
/*   Updated: 2024/10/08 11:10:53 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo, bool pre_sim)
{
	time_t	t_think;
	time_t	t_sleep;
	time_t	t_eat;

	if (!pre_sim)
		write_msg(philo, 't');
	if (philo->data->nb_of_philo % 2 == 0)
		return ;
	t_sleep = philo->data->time_to_sleep;
	t_eat = philo->data->time_to_eat;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	usleep(t_think * 1000);
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
	putdown_forks(philo);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
