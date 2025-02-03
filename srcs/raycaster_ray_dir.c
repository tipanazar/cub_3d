/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_ray_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:00:05 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:19:41 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_west_facing_wall(t_map *map, int screen_x)
{
	int current_y;
	int texture_y;
	int pixel_color;

	current_y = map->rcst->draw_start;
	while (current_y < map->rcst->draw_end)
	{
		texture_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		pixel_color = get_texture_pixel(&map->we_texture_img, map->rcst->tex_x,
							  texture_y);
		if (map->rcst->side == 1)
			pixel_color = (pixel_color >> 1) & 8355711;
		draw_pixel(map->data, screen_x, current_y, pixel_color);
		current_y++;
	}
}

void render_east_facing_wall(t_map *map, int screen_x)
{
	int current_y;
	int texture_y;
	int pixel_color;

	current_y = map->rcst->draw_start;
	while (current_y < map->rcst->draw_end)
	{
		texture_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		pixel_color = get_texture_pixel(&map->ea_texture_img, map->rcst->tex_x,
							  texture_y);
		if (map->rcst->side == 1)
			pixel_color = (pixel_color >> 1) & 8355711;
		draw_pixel(map->data, screen_x, current_y, pixel_color);
		current_y++;
	}
}

void render_north_facing_wall(t_map *map, int screen_x)
{
	int current_y;
	int texture_y;
	int pixel_color;

	current_y = map->rcst->draw_start;
	while (current_y < map->rcst->draw_end)
	{
		texture_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		pixel_color = get_texture_pixel(&map->no_texture_img, map->rcst->tex_x,
							  texture_y);
		if (map->rcst->side == 1)
			pixel_color = (pixel_color >> 1) & 8355711;
		draw_pixel(map->data, screen_x, current_y, pixel_color);
		current_y++;
	}
}

void render_south_facing_wall(t_map *map, int screen_x)
{
	int current_y;
	int texture_y;
	int pixel_color;

	current_y = map->rcst->draw_start;
	while (current_y < map->rcst->draw_end)
	{
		texture_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		pixel_color = get_texture_pixel(&map->so_texture_img, map->rcst->tex_x,
							  texture_y);
		if (map->rcst->side == 1)
			pixel_color = (pixel_color >> 1) & 8355711;
		draw_pixel(map->data, screen_x, current_y, pixel_color);
		current_y++;
	}
}

void render_wall_texture(t_map *map, int screen_x)
{
	if (map->map[map->rcst->map_y][map->rcst->map_x] == '1')
	{
		if (map->rcst->side == 0)
		{
			if (map->rcst->ray_dir_x > 0)
				render_west_facing_wall(map, screen_x);
			else
				render_east_facing_wall(map, screen_x);
		}
		else
		{
			if (map->rcst->ray_dir_y > 0)
				render_north_facing_wall(map, screen_x);
			else
				render_south_facing_wall(map, screen_x);
		}
	}
}
