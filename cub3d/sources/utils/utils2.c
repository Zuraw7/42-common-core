/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:33:26 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/06 09:33:53 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

long	get_time_in_microseconds(void)
{
	struct timeval	time;
	long			time_in_microseconds;

	gettimeofday(&time, NULL);
	time_in_microseconds = (time.tv_sec * 1000000) + time.tv_usec;
	return (time_in_microseconds);
}
