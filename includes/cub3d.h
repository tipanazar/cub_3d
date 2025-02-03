/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:58:49 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:18:25 by azhadan          ###   ########.fr       */
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

void validate_file_extension(char *file, t_map *map);
void validate_map_elements(t_map *map, char *holder_map);
bool validate_cell_boundaries(char **map, int i, int j);
bool validate_map_closure(char **map);

/*/check_map.c*/

/*close_and_free.c*/

void cleanup_resources(t_map *map);
int handle_window_close(t_map *map);
void release_texture_paths(t_map *map);
void cleanup_map_and_textures(t_map *map);
void release_map_memory(t_map *map);

/*/close_and_free.c*/

/*drawing_utils.c*/

int parse_color_component(char **color_str);
int parse_rgb_color(char *color_str, t_map *map);
void render_background(t_map *map);

/*/drawing_utils.c*/

/*init_map.c*/

void initialize_map_config(char *config_str, t_map *map);
void assign_texture(char **texture_ptr, char *texture_data, t_map *map);
void initialize_map_pointers(t_map *map);
void setup_map_from_file(char *filename, t_map *map);
void initialize_game_state(t_map *map);

/*/init_map.c*/

/*key_and_moving.c*/

int handle_keypress(int keycode, t_map *map);
int handle_keyrelease(int keycode, t_map *map);
void initialize_player_movement(t_map *map);
void handle_forward_movement(t_map *map);
void handle_backward_movement(t_map *map);

/*/key_and_moving.c*/

/*moving.c*/

void handle_strafe_left(t_map *map);
void handle_strafe_right(t_map *map);
void handle_rotation_left(t_map *map);
void handle_rotation_right(t_map *map);
void update_player_state(t_map *map);

/*/moving.c*/

/*raycaster_calculations.c*/

void initialize_ray_parameters(t_map *map, int ray_index);
void compute_ray_step_distances(t_map *map);
void execute_dda_raycast(t_map *map);
void calculate_projection_dimensions(t_map *map);
void compute_wall_texture_coordinates(t_map *map);

/*/raycaster_calculations.c*/

/*raycaster_ray_dir.c*/

void render_west_facing_wall(t_map *map, int screen_x);
void render_east_facing_wall(t_map *map, int screen_x);
void render_north_facing_wall(t_map *map, int screen_x);
void render_south_facing_wall(t_map *map, int screen_x);
void render_wall_texture(t_map *map, int screen_x);

/*/raycaster_ray_dir.c*/

/*raycaster.c*/

void render_frame(t_map *map);

/*/raycaster.c*/

/*start_game.c*/

int update_game_state(t_map *map);
void initialize_player_vectors(t_player *player, int direction_x, int direction_y);
void initialize_camera_plane(t_player *player, double plane_x, double plane_y);
void setup_player_orientation(t_player *player);
void initialize_game_window(t_map *map);

/*/start_game.c*/

/*read_map.c*/

char *extract_identifier_value(char *source_line, char *identifier);
void process_map_line(t_map *map, char **map_buffer, char *line);
void read_and_process_map(int file_descriptor, t_map *map);
void validate_map_character(t_map *map, t_player *player, int row, int col);
void validate_map_structure(t_map *map, t_player *player);

/*/read_map.c*/

/*utils.c*/

void handle_error(char *error_message, t_map *map);
void draw_pixel(t_data *buffer, int pos_x, int pos_y, int color);
t_data load_texture_image(char *texture_path, t_map *map);
int get_texture_pixel(t_data *texture, int tex_x, int tex_y);
void initialize_textures(t_map *map);

/*/utils.c*/

#endif
