/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_moving.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:43 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 12:59:44 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		ft_clear_all(map);
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

int key_release_hook(int keycode, t_map *map)
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

void init_player_speed(t_map *map)
{
	map->player->rotation_speed = 0.01;
	map->player->movement_speed = 0.01;
}

void moving_forward(t_map *map)
{
	if (map->player->moving_forward)
	{
		map->player->next_x = map->player->x + map->player->pdx * map->player->movement_speed;
		map->player->next_y = map->player->y + map->player->pdy * map->player->movement_speed;
		if (map->player->next_x >= 0 && map->player->next_y >= 0 && map->map[(int)map->player->next_y][(int)map->player->next_x] != '1')
		{
			map->player->x = map->player->next_x;
			map->player->y = map->player->next_y;
		}
	}
}

void moving_backward(t_map *map)
{
	if (map->player->moving_backward)
	{
		map->player->next_x = map->player->x - map->player->pdx * map->player->movement_speed;
		map->player->next_y = map->player->y - map->player->pdy * map->player->movement_speed;
		if (map->player->next_x >= 0 && map->player->next_y >= 0 && map->map[(int)map->player->next_y][(int)map->player->next_x] != '1')
		{
			map->player->x = map->player->next_x;
			map->player->y = map->player->next_y;
		}
	}
}
