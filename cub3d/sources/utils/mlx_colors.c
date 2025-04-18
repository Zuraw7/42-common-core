/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:18:32 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/13 22:10:09 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_colors.h"

int	get_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	get_r(int argb)
{
	return ((argb >> 24) & 0xFF);
}

int	get_g(int argb)
{
	return ((argb >> 16) & 0xFF);
}

int	get_b(int argb)
{
	return ((argb >> 8) & 0xFF);
}

int	get_a(int argb)
{
	return (argb & 0xFF);
}
