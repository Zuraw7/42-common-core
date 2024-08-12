/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:18:30 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/08 19:44:30 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// CREATES A STRING OF HOW MANY COLLECTIBLES ARE COLLECTED
char	*collected_stats(t_data *data, char *show_coll)
{
	char	*collected;
	char	*to_collect;
	int		len;

	collected = ft_itoa(data->player.collected);
	to_collect = ft_itoa(data->to_collect);
	len = ft_strlen("Collected: ") + ft_strlen(collected)
		+ ft_strlen(" / ") + ft_strlen(to_collect) + 1;
	show_coll = malloc(len * sizeof(char));
	if (!show_coll)
		return (NULL);
	ft_strcpy(show_coll, "Collected: ");
	ft_strcat(show_coll, collected);
	ft_strcat(show_coll, " / ");
	ft_strcat(show_coll, to_collect);
	free(collected);
	free(to_collect);
	return (show_coll);
}

// CREATES A STRING ABOUT THE NUMBER OF STRINGS
char	*move_stats(t_data *data, char *show_moves)
{
	char	*moves;
	int		len;

	moves = ft_itoa(data->player.moves);
	len = ft_strlen("Moves: ") + ft_strlen(moves) + 1;
	show_moves = malloc(len * sizeof(char));
	ft_strcpy(show_moves, "Moves: ");
	ft_strcat(show_moves, moves);
	free(moves);
	return (show_moves);
}

static void	put_bold_text(t_data *data, int color, int x, char *text)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, 16, color, text);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x + 1, 16, color, text);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, 16 + 1, color, text);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x + 1, 16 + 1, color, text);
}

// PUTS BOTH STATS TO THE SCREEN
int	put_stats(t_data *data)
{
	char	*show_coll;
	char	*show_moves;
	int		color;

	show_coll = NULL;
	show_moves = NULL;
	color = 0x00FFFFFF;
	show_coll = collected_stats(data, show_coll);
	put_bold_text(data, color, (data->map.map_width * TILE_SIZE)
		/ 2 - 128, show_coll);
	show_moves = move_stats(data, show_moves);
	put_bold_text(data, color, (data->map.map_width * TILE_SIZE)
		/ 2 + 64, show_moves);
	free_strings(show_coll, show_moves);
	return (0);
}
