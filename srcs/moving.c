/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:54 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 12:59:55 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void moving_left(t_map *map)
{
	if (map->player->moving_left)
	{
		map->player->next_x = map->player->x + map->player->pdy * map->player->movement_speed;
		map->player->next_y = map->player->y - map->player->pdx * map->player->movement_speed;
		if (map->player->next_x >= 0 && map->player->next_y >= 0 && map->map[(int)map->player->next_y][(int)map->player->next_x] != '1')
		{
			map->player->x = map->player->next_x;
			map->player->y = map->player->next_y;
		}
	}
}

void moving_right(t_map *map)
{
	if (map->player->moving_right)
	{
		map->player->next_x = map->player->x - map->player->pdy * map->player->movement_speed;
		map->player->next_y = map->player->y + map->player->pdx * map->player->movement_speed;
		if (map->player->next_x >= 0 && map->player->next_y >= 0 && map->map[(int)map->player->next_y][(int)map->player->next_x] != '1')
		{
			map->player->x = map->player->next_x;
			map->player->y = map->player->next_y;
		}
	}
}

void rotating_left(t_map *map)
{
	if (map->player->rotating_left)
	{
		map->player->old_dir_x = map->player->pdx;
		map->player->pdx = map->player->pdx * cos(-map->player->rotation_speed) - map->player->pdy * sin(-map->player->rotation_speed);
		map->player->pdy = map->player->old_dir_x * sin(-map->player->rotation_speed) + map->player->pdy * cos(-map->player->rotation_speed);
		map->player->old_plane_x = map->player->plane_x;
		map->player->plane_x = map->player->plane_x * cos(-map->player->rotation_speed) - map->player->plane_y * sin(-map->player->rotation_speed);
		map->player->plane_y = map->player->old_plane_x * sin(-map->player->rotation_speed) + map->player->plane_y * cos(-map->player->rotation_speed);
	}
}

void rotating_right(t_map *map)
{
	if (map->player->rotating_right)
	{
		map->player->old_dir_x = map->player->pdx;
		map->player->pdx = map->player->pdx * cos(map->player->rotation_speed) - map->player->pdy * sin(map->player->rotation_speed);
		map->player->pdy = map->player->old_dir_x * sin(map->player->rotation_speed) + map->player->pdy * cos(map->player->rotation_speed);
		map->player->old_plane_x = map->player->plane_x;
		map->player->plane_x = map->player->plane_x * cos(map->player->rotation_speed) - map->player->plane_y * sin(map->player->rotation_speed);
		map->player->plane_y = map->player->old_plane_x * sin(map->player->rotation_speed) + map->player->plane_y * cos(map->player->rotation_speed);
	}
}

void update_player(t_map *map)
{
	init_player_speed(map);
	moving_forward(map);
	moving_backward(map);
	moving_left(map);
	moving_right(map);
	rotating_left(map);
	rotating_right(map);
	clear_screen(map);
	raycaster_loop(map);
}
