/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_moving.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:43 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:03:44 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_keypress(int keycode, t_map *map)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		cleanup_resources(map);
		exit(0);
	}
	else if (keycode == KEY_W || keycode == KEY_LINUX_W)
		map->player->moving_forward = 1;
	else if (keycode == KEY_S || keycode == KEY_LINUX_S)
		map->player->moving_backward = 1;
	else if (keycode == KEY_A || keycode == KEY_LINUX_A)
		map->player->moving_left = 1;
	else if (keycode == KEY_D || keycode == KEY_LINUX_D)
		map->player->moving_right = 1;
	else if (keycode == KEY_LINUX_LEFT || keycode == KEY_LEFT)
		map->player->rotating_left = 1;
	else if (keycode == KEY_LINUX_RIGHT || keycode == KEY_RIGHT)
		map->player->rotating_right = 1;
	return (0);
}

int handle_keyrelease(int keycode, t_map *map)
{
	if (keycode == KEY_W || keycode == KEY_LINUX_W)
		map->player->moving_forward = 0;
	else if (keycode == KEY_S || keycode == KEY_LINUX_S)
		map->player->moving_backward = 0;
	else if (keycode == KEY_A || keycode == KEY_LINUX_A)
		map->player->moving_left = 0;
	else if (keycode == KEY_D || keycode == KEY_LINUX_D)
		map->player->moving_right = 0;
	else if (keycode == KEY_LINUX_LEFT || keycode == KEY_LEFT)
		map->player->rotating_left = 0;
	else if (keycode == KEY_LINUX_RIGHT || keycode == KEY_RIGHT)
		map->player->rotating_right = 0;
	return (0);
}

void initialize_player_movement(t_map *map)
{
	map->player->rotation_speed = 0.01;
	map->player->movement_speed = 0.01;
}

void handle_forward_movement(t_map *map)
{
	float next_position_x;
	float next_position_y;

	if (map->player->moving_forward)
	{
		next_position_x = map->player->x + map->player->pdx * map->player->movement_speed;
		next_position_y = map->player->y + map->player->pdy * map->player->movement_speed;
		if (next_position_x >= 0 && next_position_y >= 0 && 
			map->map[(int)next_position_y][(int)next_position_x] != '1')
		{
			map->player->x = next_position_x;
			map->player->y = next_position_y;
		}
	}
}

void handle_backward_movement(t_map *map)
{
	float next_position_x;
	float next_position_y;

	if (map->player->moving_backward)
	{
		next_position_x = map->player->x - map->player->pdx * map->player->movement_speed;
		next_position_y = map->player->y - map->player->pdy * map->player->movement_speed;
		if (next_position_x >= 0 && next_position_y >= 0 && 
			map->map[(int)next_position_y][(int)next_position_x] != '1')
		{
			map->player->x = next_position_x;
			map->player->y = next_position_y;
		}
	}
}
