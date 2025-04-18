/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:49:59 by astefans          #+#    #+#             */
/*   Updated: 2025/04/13 22:11:15 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_COLORS_H
# define MLX_COLORS_H

// 'Encodes' four individual bytes into an int
int	get_argb(int a, int r, int g, int b);

// Get the red channel
int	get_r(int argb);

// Get the green channel
int	get_g(int argb);

// Get the blue channel
int	get_b(int argb);

// Get the alpha channel
int	get_a(int argb);

#endif