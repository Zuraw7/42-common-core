/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:57:32 by pzurawic          #+#    #+#             */
/*   Updated: 2024/09/07 13:27:11 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// CHANGES STRING INTO NUMBER
static int	ft_atoi(const char *nptr)
{
	char	*snum;
	int		num;
	int		sign;

	sign = 1;
	snum = (char *)nptr;
	num = 0;
	while (*snum == '\t' || *snum == '\n' || *snum == '\r'
		|| *snum == '\v' || *snum == '\f' || *snum == ' ')
		snum++;
	if (*snum == '-' || *snum == '+')
	{
		if (*snum == '-')
			sign *= -1;
		else
			sign = 1;
		snum++;
	}
	while (*snum >= '0' && *snum <= '9')
	{
		num = num * 10 + (*snum - '0');
		snum++;
	}
	return (num * sign);
}

static bool	is_number(char c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}

static int	set_data(t_data *data, char **argv, int argc)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	if (data->nb_of_philo > 200 || data->nb_of_philo < 1)
		return (printf("Wrong amount of philos\n"), 1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->how_much_to_eat = ft_atoi(argv[5]);
	else
		data->how_much_to_eat = -1;
	data->philo_finished = 0;
	data->sim_status = true;
	data->tid = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->tid)
		return (printf("%s", THREAD_ALLOC_FAIL), 1);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->simulation_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	return (0);
}

// CHECKS IF THERE IS A NON NUMBER CHARACTER IN STRING
void	check_input(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (is_number(argv[i][j]) == false)
			{
				printf("Positive numbers only in input\n");
				exit (1);
			}
			j++;
		}
		i++;
	}
	if (set_data(data, argv, argc) == 1)
		exit (1);
}
