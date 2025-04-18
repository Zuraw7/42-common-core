/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <astefans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:03:48 by zuraw             #+#    #+#             */
/*   Updated: 2025/04/15 19:55:46 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/time.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "mlx_colors.h"

/*	DEFINES	*/

# define WIDTH 800
# define HEIGHT 600
# define OFFSET 0.15
# define TARGET_FPS 144
# define FRAME_TIME 6944.444444444
# define PX 32
# define PI 3.14159265359
# define TEX_SIZE 64
# define SENSITIVITY 0.0001
# define INPUT_ERROR "Error: Invalid input\nUsage: ./cub3d <map.cub>"
# define READ_ERROR "Error: Failed to load map\n"
# define VAL_CONFIG_ERROR "Error: Invalid map configuration\n"
# define VAL_ERROR "Error: Invalid map\n"
# define TEXTURES_ERROR "Error: Invalid textures\n"
# define COLORS_ERROR "Error: Invalid colors\n"
# define INFO_ERROR "File should contain NO, EA, SO, WE, C, F \
and map structure only\n"

/*	STRUCTS	*/

typedef struct s_data		t_data;
typedef struct s_mlx		t_mlx;
typedef struct s_bfs		t_bfs;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_img		t_img;
typedef struct s_rend_img	t_rend_img;
typedef struct s_keys		t_keys;

typedef enum e_main_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
}				t_main_direction;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	long	last_time;
	t_data	*data;
}				t_mlx;

// Breadth-First Search
typedef struct s_bfs
{
	int		x;
	int		y;
	t_bfs	*next;
}				t_bfs;

typedef struct s_map
{
	int		floor_color;		
	int		ceiling_color;		
	char	**hold_cf_color;
	char	**nesw_textures;
	char	**file;
	char	**map;
	int		width;
	int		height;
	t_data	*data;
	t_bfs	*queue;
}				t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	dir;	
	float	plane_x;			
	float	plane_y;			
	char	start_dir;			
	t_data	*data;				
}				t_player;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	int		mouse;
}	t_keys;

typedef struct s_ray_vars
{
	double	wall_dist;
	double	step;
	double	tex_position;
	double	wallx;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	int		offset;
	int		color;
	int		bytes_per_pixel;
}	t_ray_vars;

typedef struct s_ray
{
	double	camera_x;			
	double	delta_x;		
	double	delta_y;			
	double	side_x;				
	double	side_y;				
	double	perpwalldist;		
	int		map_x;			
	int		map_y;				
	int		step_x;				
	int		step_y;			
	int		side;				
	int		hit;			
	double	pos_x;				
	double	pos_y;				
	double	dir_x;			
	double	dir_y;				
	double	plane_x;			
	double	plane_y;			
	t_data	*data;				
}				t_ray;

typedef struct s_img
{
	void	*img_ptr;			
	char	*addr;				
	int		bits_per_pixel;		
	int		line_length;		
	int		endian;				
	int		width;				
	int		height;				
	t_data	*data;				
}				t_img;

typedef struct s_rend_img
{
	t_img	*minimap;			
	t_img	*player_mm;			
	t_img	*rays;				
	t_img	*walls[4];			
	t_data	*data;				
}			t_rend_img;

typedef struct s_data
{
	t_mlx		*mlx;		
	t_map		*map;		
	t_player	*player;		
	t_rend_img	*rend_img;	
	t_ray		*ray;		
	t_keys		keys;
}				t_data;

/*	FUNCTIONS	*/

/*---window_management---*/

// open_close.c
void	open_window(t_mlx *mlx);
int		close_window(t_data *data);

/*---move-events---*/

// keyboard_input.c
void	register_events(t_data *data);

// mouse_input.c
int		mouse_move(int x, int y, t_data *data);

// player_move.c
void	move_player(t_player *player, int keycode);
void	handle_movement(t_player *player, t_keys *keys);

// rotate_player.c
void	rotate_player(t_player *player, int keycode);

/*---utils---*/

// utils.c
void	*my_realloc(void *ptr, size_t old_size, size_t new_size);
int		ft_isspace(char c);
int		is_line_empty(char *line);
char	*make_set(char *list);
void	set_player_dir(t_player *player);

// utils2.c
long	get_time_in_microseconds(void);

// clear.c
void	exit_clear(t_data *data);
void	free_double_arr(char **arr);
void	clear_queue(t_bfs *queue);

// set_data.c
void	set_data(t_data *data);

// set_data_utils.c
t_mlx	*set_mlx(t_data *data);
t_map	*set_map(t_data *data);

// clear_map.c
void	free_map(t_map *map);
void	free_cf_color(t_map *map);

// mlx_colors.c
int		get_argb(int a, int r, int g, int b);
int		get_r(int argb);
int		get_g(int argb);
int		get_b(int argb);
int		get_a(int argb);

// parse_map_utils.c
int		valid_colors(t_map *map);

// inits.c
t_bfs	*init_queue(int x, int y);
t_img	*init_img(t_data *data, void *mlx_ptr, int width, int height);

/*---map_reader---*/

// copy_map_file.c
char	**read_map(char *file);

// process_map_file.c
int		process_map_file(t_map *map, char *file);

// validate_map_config.c
int		validate_map_config(t_map *map);

// valid_texture.c
int		valid_textures(t_map *map);

// check_colors.c
int		check_colors(t_map *map);

// validate_map_config_utils.c
char	**alloc_nesw(void);
char	**alloc_color(void);
void	set_tex_path(t_map *map, int i, char *line, int *count);
int		check_is_map(char *line);

// validate_map.c
int		validate_map(t_map *map);
char	**bfs_map(t_map *map);

// validate_map_copy_map.c
int		copy_map(t_map *map);

// valid_map_structure.c
int		valid_map_structure(t_map *map);

// valid_map_structure_utils.c
int		check_neighbour(char **map, char *set, int i, int j);
void	count_p_pos(t_map *map, int i, int j, int *pp);
void	calc_width_height(t_map *map);

// check_walls.c
int		check_walls(t_map *map);

// input_validation.c
void	input_checker(int argc, char **argv);

/*---raycasting---*/

//raycasting.c
int		raycaster(t_data *data);

//ray_helper.c
int		init_ray(t_ray *ray, t_data *data, int x);
void	calculate_step(t_ray *ray, double pos_x, double pos_y);
void	cast_ray(t_data *data, t_ray *ray);

//ray_utils.c
double	get_wallx(t_ray *ray);
void	draw_ceiling_and_floor(t_data *data);
void	perp_wall_dist(t_ray *ray);

// create_img.c
void	render_imgs(t_data *data);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	draw_tile_to_minimap(t_img *img, int x, int y, int color);

// draw_player_map.c
void	draw_minimap(t_data *data);
void	draw_player(t_img *img);
void	render_scene(t_data *data);

#endif