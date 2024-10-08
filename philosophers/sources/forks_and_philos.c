/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_and_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:57:18 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/05 10:29:55 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	initialize_philos(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
	{
		printf("Failed to alloc philos\n");
		i = -1;
		while (++i < data->nb_of_philo)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].finished_eating = false;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->nb_of_philo];
		pthread_mutex_init(&data->philo[i].meal_update, NULL);
		i++;
	}
	return (0);
}

static int	initialize_forks(t_data *data)
{
	int	i;
	int	j;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->forks)
	{
		printf("Failed to alloc forks\n");
		return (1);
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Failed to initialize mutex\n");
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&data->forks[j]);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_forks_and_philos(t_data *data)
{
	if (initialize_forks(data) == 1)
		exit (1);
	if (initialize_philos(data) == 1)
		exit (1);
}
