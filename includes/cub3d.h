/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:58:49 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 14:54:34 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx_opengl/mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PI 3.14159265358979323846
#define KEY_ESC 65307
#define KEY_Q 113
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 0x7B
#define KEY_RIGHT 0x7C
#define KEY_LINUX_LEFT 65361
#define KEY_LINUX_RIGHT 65363
#define KEY_LINUX_W 119
#define KEY_LINUX_A 97
#define KEY_LINUX_S 115
#define KEY_LINUX_D 100
#define DR 0.0174533
#define FOV 60
#define TILE_SIZE 20
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define EPSILON 0.0001
#define CLOCKS_PER_SEC 1000000
#define TEXTURE_SIZE 64

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_window
{
	void *mlx_ptr;
	void *win_ptr;
} t_window;

typedef struct s_player
{
	float x;
	float y;
	float pdx;
	float pdy;
	float pa;
	char p_direction;
	int moving_forward;
	int moving_backward;
	int moving_left;
	int moving_right;
	int rotating_left;
	int rotating_right;
	double plane_x;
	double plane_y;
	double old_dir_x;
	double old_plane_x;
	float rotation_speed;
	float movement_speed;
	float next_x;
	float next_y;
} t_player;

typedef struct s_rcst
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
	int color;
	double wall_x;
	int tex_x;
	int tex_y;
	double step;
	double tex_pos;
	int tex_num;
} t_rcst;

typedef struct s_map
{
	char **map;
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	char *floor_color;
	char *ceiling_color;
	int floor_color_int;
	int ceiling_color_int;
	t_data no_texture_img;
	t_data so_texture_img;
	t_data we_texture_img;
	t_data ea_texture_img;
	t_data *data;
	t_player *player;
	t_window *window;
	t_rcst *rcst;
	bool flag;
} t_map;

/*check_map.c*/

void check_path(char *file, t_map *map);
void check_textures_and_colors(t_map *map, char *holder_map);
bool is_cell_closed(char **map, int i, int j);
bool is_map_closed(char **map);

/*/check_map.c*/

/*close_and_free.c*/

void ft_clear_all(t_map *map);
int ft_close_win(t_map *map);
void free_textures_and_colors(t_map *map);
void free_map_and_images(t_map *map);
void free_map(t_map *map);

/*/close_and_free.c*/

/*drawing_utils.c*/

int validate_and_parse_number(char **str);
int get_the_color(char *str, t_map *map);
void clear_screen(t_map *map);

/*/drawing_utils.c*/

/*init_map.c*/

void map_init(char *str, t_map *map);
void set_texture(char **texture, char *saved_line, t_map *map);
void init_map_data(t_map *map);
void open_and_init_map(char *file, t_map *map);
void init(t_map *map);

/*/init_map.c*/

/*key_and_moving.c*/

int key_press_hook(int keycode, t_map *map);
int key_release_hook(int keycode, t_map *map);
void init_player_speed(t_map *map);
void moving_forward(t_map *map);
void moving_backward(t_map *map);

/*/key_and_moving.c*/

/*moving.c*/

void moving_left(t_map *map);
void moving_right(t_map *map);
void rotating_left(t_map *map);
void rotating_right(t_map *map);
void update_player(t_map *map);

/*/moving.c*/

/*raycaster_calculations.c*/

void init_raycaster_data(t_map *map, int i);
void calculate_step_and_side_distances(t_map *map);
void perform_dda_algorithm(t_map *map);
void calculate_wall_distance_and_line_height(t_map *map);
void calculate_draw_start_end_and_wall_x(t_map *map);

/*/raycaster_calculations.c*/

/*raycaster_ray_dir.c*/

void handle_ray_dir_x_positive(t_map *map, int i);
void handle_ray_dir_x_negative(t_map *map, int i);
void handle_ray_dir_y_positive(t_map *map, int i);
void handle_ray_dir_y_negative(t_map *map, int i);
void handle_ray_direction(t_map *map, int i);

/*/raycaster_ray_dir.c*/

/*raycaster.c*/

void raycaster_loop(t_map *map);

/*/raycaster.c*/

/*start_game.c*/

int game_loop(t_map *map);
void set_player_direction(t_player *player, int pdx, int pdy);
void set_player_plane(t_player *player, double plane_x,
					  double plane_y);
void initialize_player_direction(t_player *player);
void game_start(t_map *map);

/*/start_game.c*/

/*read_map.c*/

char *save_the_line(char *line, char *to_find);
void process_line(t_map *map, char **holder_map, char *line);
void process_map_lines(int fd, t_map *map);
void process_map_symbol(t_map *map, t_player *player, int i, int j);
void map_validation(t_map *map, t_player *player);

/*/read_map.c*/

/*utils.c*/

void err(char *str, t_map *map);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_data create_img(char *path, t_map *map);
int get_pixel(t_data *img, int x, int y);
void load_textures(t_map *map);

/*/utils.c*/

#endif
