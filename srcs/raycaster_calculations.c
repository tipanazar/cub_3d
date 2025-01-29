/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_calculations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:59 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 13:00:01 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_raycaster_data(t_map *map, int i)
{
	map->rcst->camera_x = 2 * i / (double)WINDOW_WIDTH - 1;
	map->rcst->ray_dir_x = map->player->pdx + map->player->plane_x * map->rcst->camera_x;
	map->rcst->ray_dir_y = map->player->pdy + map->player->plane_y * map->rcst->camera_x;
	map->rcst->map_x = (int)map->player->x;
	map->rcst->map_y = (int)map->player->y;
	if (map->rcst->ray_dir_x == 0)
		map->rcst->delta_dist_x = 1e30;
	else
		map->rcst->delta_dist_x = fabs(1 / map->rcst->ray_dir_x);
	if (map->rcst->ray_dir_y == 0)
		map->rcst->delta_dist_y = 1e30;
	else
		map->rcst->delta_dist_y = fabs(1 / map->rcst->ray_dir_y);
	map->rcst->hit = 0;
}

void calculate_step_and_side_distances(t_map *map)
{
	if (map->rcst->ray_dir_x < 0)
	{
		map->rcst->step_x = -1;
		map->rcst->side_dist_x = (map->player->x - map->rcst->map_x) * map->rcst->delta_dist_x;
	}
	else
	{
		map->rcst->step_x = 1;
		map->rcst->side_dist_x = (map->rcst->map_x + 1.0 - map->player->x) * map->rcst->delta_dist_x;
	}
	if (map->rcst->ray_dir_y < 0)
	{
		map->rcst->step_y = -1;
		map->rcst->side_dist_y = (map->player->y - map->rcst->map_y) * map->rcst->delta_dist_y;
	}
	else
	{
		map->rcst->step_y = 1;
		map->rcst->side_dist_y = (map->rcst->map_y + 1.0 - map->player->y) * map->rcst->delta_dist_y;
	}
}

void perform_dda_algorithm(t_map *map)
{
	while (map->rcst->hit == 0)
	{
		if (map->rcst->side_dist_x < map->rcst->side_dist_y)
		{
			map->rcst->side_dist_x += map->rcst->delta_dist_x;
			map->rcst->map_x += map->rcst->step_x;
			map->rcst->side = 0;
		}
		else
		{
			map->rcst->side_dist_y += map->rcst->delta_dist_y;
			map->rcst->map_y += map->rcst->step_y;
			map->rcst->side = 1;
		}
		if (map->map[map->rcst->map_y][map->rcst->map_x] == '1')
			map->rcst->hit = 1;
	}
}

void calculate_wall_distance_and_line_height(t_map *map)
{
	if (map->rcst->side == 0)
		map->rcst->perp_wall_dist = map->rcst->side_dist_x - map->rcst->delta_dist_x;
	else
		map->rcst->perp_wall_dist = map->rcst->side_dist_y - map->rcst->delta_dist_y;
	map->rcst->line_height = (int)(WINDOW_HEIGHT / map->rcst->perp_wall_dist);
}

void calculate_draw_start_end_and_wall_x(t_map *map)
{
	map->rcst->draw_start = (-1) * map->rcst->line_height / 2 + WINDOW_HEIGHT / 2;
	if (map->rcst->draw_start < 0)
		map->rcst->draw_start = 0;
	map->rcst->draw_end = map->rcst->line_height / 2 + WINDOW_HEIGHT / 2;
	if (map->rcst->draw_end >= WINDOW_HEIGHT)
		map->rcst->draw_end = WINDOW_HEIGHT - 1;
	if (map->rcst->side == 0)
		map->rcst->wall_x = map->player->y + map->rcst->perp_wall_dist * map->rcst->ray_dir_y;
	else
		map->rcst->wall_x = map->player->x + map->rcst->perp_wall_dist * map->rcst->ray_dir_x;
	map->rcst->wall_x -= floor(map->rcst->wall_x);
	map->rcst->tex_x = (int)(map->rcst->wall_x * (double)TEXTURE_SIZE);
	if (map->rcst->side == 0 && map->rcst->ray_dir_x > 0)
		map->rcst->tex_x = TEXTURE_SIZE - map->rcst->tex_x - 1;
	if (map->rcst->side == 1 && map->rcst->ray_dir_y < 0)
		map->rcst->tex_x = TEXTURE_SIZE - map->rcst->tex_x - 1;
	map->rcst->step = 1.0 * TEXTURE_SIZE / map->rcst->line_height;
	map->rcst->tex_pos = (map->rcst->draw_start - WINDOW_HEIGHT / 2 + map->rcst->line_height / 2) * map->rcst->step;
}
