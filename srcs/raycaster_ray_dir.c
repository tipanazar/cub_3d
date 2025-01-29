/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_ray_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:00:05 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 13:00:07 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_ray_dir_x_positive(t_map *map, int i)
{
	map->rcst->tex_num = map->rcst->draw_start;
	while (map->rcst->tex_num < map->rcst->draw_end)
	{
		map->rcst->tex_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		map->rcst->color = get_pixel(&map->we_texture_img, map->rcst->tex_x,
									 map->rcst->tex_y);
		if (map->rcst->side == 1)
			map->rcst->color = (map->rcst->color >> 1) & 8355711;
		my_mlx_pixel_put(map->data, i, map->rcst->tex_num, map->rcst->color);
		map->rcst->tex_num++;
	}
}

void handle_ray_dir_x_negative(t_map *map, int i)
{
	map->rcst->tex_num = map->rcst->draw_start;
	while (map->rcst->tex_num < map->rcst->draw_end)
	{
		map->rcst->tex_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		map->rcst->color = get_pixel(&map->ea_texture_img, map->rcst->tex_x,
									 map->rcst->tex_y);
		if (map->rcst->side == 1)
			map->rcst->color = (map->rcst->color >> 1) & 8355711;
		my_mlx_pixel_put(map->data, i, map->rcst->tex_num, map->rcst->color);
		map->rcst->tex_num++;
	}
}

void handle_ray_dir_y_positive(t_map *map, int i)
{
	map->rcst->tex_num = map->rcst->draw_start;
	while (map->rcst->tex_num < map->rcst->draw_end)
	{
		map->rcst->tex_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		map->rcst->color = get_pixel(&map->no_texture_img, map->rcst->tex_x,
									 map->rcst->tex_y);
		if (map->rcst->side == 1)
			map->rcst->color = (map->rcst->color >> 1) & 8355711;
		my_mlx_pixel_put(map->data, i, map->rcst->tex_num, map->rcst->color);
		map->rcst->tex_num++;
	}
}

void handle_ray_dir_y_negative(t_map *map, int i)
{
	map->rcst->tex_num = map->rcst->draw_start;
	while (map->rcst->tex_num < map->rcst->draw_end)
	{
		map->rcst->tex_y = (int)map->rcst->tex_pos & (TEXTURE_SIZE - 1);
		map->rcst->tex_pos += map->rcst->step;
		map->rcst->color = get_pixel(&map->so_texture_img, map->rcst->tex_x,
									 map->rcst->tex_y);
		if (map->rcst->side == 1)
			map->rcst->color = (map->rcst->color >> 1) & 8355711;
		my_mlx_pixel_put(map->data, i, map->rcst->tex_num, map->rcst->color);
		map->rcst->tex_num++;
	}
}

void handle_ray_direction(t_map *map, int i)
{
	if (map->map[map->rcst->map_y][map->rcst->map_x] == '1')
	{
		if (map->rcst->side == 0)
		{
			if (map->rcst->ray_dir_x > 0)
				handle_ray_dir_x_positive(map, i);
			else
				handle_ray_dir_x_negative(map, i);
		}
		else
		{
			if (map->rcst->ray_dir_y > 0)
				handle_ray_dir_y_positive(map, i);
			else
				handle_ray_dir_y_negative(map, i);
		}
	}
}
