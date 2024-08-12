/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:32:47 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/03 12:17:50 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// HANDLES WASD, ESC AND ENTER EVENTS
int	key_checker(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		do_destroy(data);
		exit(0);
	}
	else if (keysym == XK_w || keysym == XK_a
		|| keysym == XK_s || keysym == XK_d || keysym == 65293)
	{
		wasd_move(keysym, data);
		ft_printf("moves: %d\n", data->player.moves);
	}
	return (0);
}

void	input_handler(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_checker, data);
}
