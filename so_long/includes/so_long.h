/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <pzurawic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:27:48 by pzurawic          #+#    #+#             */
/*   Updated: 2024/08/10 16:59:46 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h> 
# include <stdio.h>
# include <string.h>

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_player
{
	int		char_width;
	int		char_height;
	int		moves;
	int		collected;
	int		pos_x;
	int		pos_y;
	int		frame;
	int		tot_frames;
	void	*textures[8];
}	t_player;

typedef struct s_enemies
{
	int					x;
	int					y;
	struct s_enemies	*next;
}	t_enemies;

typedef struct s_map
{
	int		files_height;
	int		files_width;
	char	*starting_pos;
	char	**map_data;
	int		exit_x;
	int		exit_y;
	int		map_width;
	int		map_height;
}	t_map;

typedef struct s_gnl
{
	char	*buffer;
}	t_gnl;

typedef struct s_queue
{
	int				x;
	int				y;
	char			c;
	struct s_queue	*next;
}	t_queue;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*textures[4];
	void		*en_textures[4];
	int			to_collect;
	int			game_on;
	t_queue		*queue;
	t_enemies	*enemies;
	t_map		map;
	t_player	player;
	t_gnl		gnl;
}	t_data;

typedef struct s_bfs_params
{
	t_data	*data;
	int		*check_coll;
	int		*check_exit;
	char	**map;
}	t_bfs_params;

// CLOSE WINDOW EVENT
void	close_window_hook(t_data *data);
int		close_window(t_data *data);
void	do_destroy(t_data *data);

// INPUT HANDLING
void	input_handler(t_data *data);
int		key_checker(int keysym, t_data *data);
int		wasd_move(int keysym, t_data *data);

// MAP HANDLING
void	load_textures(t_data *data);
void	check_textures(t_data *data);
void	read_map(char *filename, t_data *data);
void	draw_map(t_data *data);
void	put_map(t_data *data, char loc, int x, int y);
void	free_map_data(t_data *data);
char	*get_nl(int fd, t_gnl *gnl);
void	cleanup_get_next_line(t_data *data);

// CHECKING MAP ERRORS
void	map_checker(t_data *data);
void	map_invalid_error(t_data *data);
void	is_rectangle(t_data *data);
void	check_walls(t_data *data);
void	check_if_playable(t_data *data);

// MAP ERRORS -> IS WINNABLE CHECKING SYSTEM
char	**set_map(t_data *data);
void	check_and_add(t_bfs_params *params, int x, int y);
void	bfs(t_data *data, int *check_coll, int *check_exit, char **map);
void	check_if_winnable(t_data *data);

// IS WINNABLE CHECKING SYSTEM UTILS
t_queue	*add_to_queue(t_data *data, int x, int y, char **map);
t_queue	*set_queue_start(t_queue **queue, t_data *data, char **map);
void	free_q_and_map(t_data *data, char **map);

// GAME INFO
void	show_stats(t_data *data);
int		put_stats(t_data *data);
void	free_strings(char *show_coll, char *show_moves);
char	*collected_stats(t_data *data, char *show_coll);
char	*move_stats(t_data *data, char *show_moves);

// GAME INFO UTILS
void	ft_strcpy(char *dest, char *src);
void	ft_strcat(char *dest, char *src);

// ENEMIES
void	free_all_enemies(t_data *data);
void	check_if_lose(int keysym, t_data *data);
void	move_towards_player(t_data *data);
void	set_enemies(t_data *data);

// ANIMATIONS
int		animation(t_data *data);

#endif
