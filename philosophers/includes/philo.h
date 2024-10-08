/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:52 by pzurawic          #+#    #+#             */
/*   Updated: 2024/10/08 11:11:31 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <aio.h>
# include <sys/time.h>

/*	MACROS */
# define INPUT_ERROR "Program usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
*[number_of_each_times_each_philosopher_must_eat]\n"
# define THREAD_ALLOC_FAIL "Could not alloc threads\n"
# define CREATE_FAIL "Failed to create thread\n"
# define JOIN_FAIL "Failed to join thread\n"

/* STRUCTS */
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			finished_eating;

	time_t			last_meal_time;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_update;

	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				nb_of_philo;
	int				how_much_to_eat;
	int				philo_finished;
	bool			sim_status;

	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;	
	pthread_mutex_t	simulation_lock;
	pthread_mutex_t	meal_lock;
	struct s_philo	*philo;
}	t_data;

/*	FUNCTIONS */
// UTILS
time_t	get_time(void);
void	exit_clearly(t_data *data);

//INPUT_CHECKER
void	check_input(int argc, char **argv, t_data *data);

// FORKS_AND_PHILOS
void	init_forks_and_philos(t_data *data);

// SIMULATION
void	run_simulation(t_data *data);
void	end_simulation(t_data *data);

// SIMULATION_UTILS
void	update_meals(t_philo *philo);
void	write_msg(t_philo *philo, char c);
int		check_sim_status(t_philo *philo);

// ONE_PHILO_CASE
void	one_philo_case(t_data *data);

// ACTIVITIES
void	thinking(t_philo *philo, bool pre_sim);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	putdown_forks(t_philo *philo);

#endif