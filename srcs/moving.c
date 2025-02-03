/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:54 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:14:03 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_strafe_left(t_map *map)
{
	float next_position_x;
	float next_position_y;

	if (map->player->moving_left)
	{
		next_position_x = map->player->x + map->player->pdy * map->player->movement_speed;
		next_position_y = map->player->y - map->player->pdx * map->player->movement_speed;
		if (next_position_x >= 0 && next_position_y >= 0 && 
			map->map[(int)next_position_y][(int)next_position_x] != '1')
		{
			map->player->x = next_position_x;
			map->player->y = next_position_y;
		}
	}
}

void handle_strafe_right(t_map *map)
{
	float next_position_x;
	float next_position_y;

	if (map->player->moving_right)
	{
		next_position_x = map->player->x - map->player->pdy * map->player->movement_speed;
		next_position_y = map->player->y + map->player->pdx * map->player->movement_speed;
		if (next_position_x >= 0 && next_position_y >= 0 && 
			map->map[(int)next_position_y][(int)next_position_x] != '1')
		{
			map->player->x = next_position_x;
			map->player->y = next_position_y;
		}
	}
}

void handle_rotation_left(t_map *map)
{
	double old_direction_x;
	double old_camera_plane_x;

	if (map->player->rotating_left)
	{
		old_direction_x = map->player->pdx;
		map->player->pdx = map->player->pdx * cos(-map->player->rotation_speed) - 
						  map->player->pdy * sin(-map->player->rotation_speed);
		map->player->pdy = old_direction_x * sin(-map->player->rotation_speed) + 
						  map->player->pdy * cos(-map->player->rotation_speed);
		old_camera_plane_x = map->player->plane_x;
		map->player->plane_x = map->player->plane_x * cos(-map->player->rotation_speed) - 
							  map->player->plane_y * sin(-map->player->rotation_speed);
		map->player->plane_y = old_camera_plane_x * sin(-map->player->rotation_speed) + 
							  map->player->plane_y * cos(-map->player->rotation_speed);
	}
}

void handle_rotation_right(t_map *map)
{
	double old_direction_x;
	double old_camera_plane_x;

	if (map->player->rotating_right)
	{
		old_direction_x = map->player->pdx;
		map->player->pdx = map->player->pdx * cos(map->player->rotation_speed) - 
						  map->player->pdy * sin(map->player->rotation_speed);
		map->player->pdy = old_direction_x * sin(map->player->rotation_speed) + 
						  map->player->pdy * cos(map->player->rotation_speed);
		old_camera_plane_x = map->player->plane_x;
		map->player->plane_x = map->player->plane_x * cos(map->player->rotation_speed) - 
							  map->player->plane_y * sin(map->player->rotation_speed);
		map->player->plane_y = old_camera_plane_x * sin(map->player->rotation_speed) + 
							  map->player->plane_y * cos(map->player->rotation_speed);
	}
}

void update_player_state(t_map *map)
{
	initialize_player_movement(map);
	handle_forward_movement(map);
	handle_backward_movement(map);
	handle_strafe_left(map);
	handle_strafe_right(map);
	handle_rotation_left(map);
	handle_rotation_right(map);
	render_background(map);
	render_frame(map);
}
