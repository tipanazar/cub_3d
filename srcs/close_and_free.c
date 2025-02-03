/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:26 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 01:51:21 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	cleanup_resources(t_map *map)
// {
// 	release_map_memory(map);
// 	mlx_destroy_image(map->window->mlx_ptr, map->data->img);
// 	mlx_destroy_window(map->window->mlx_ptr, map->window->win_ptr);
// 	mlx_destroy_display(map->window->mlx_ptr);
// 	free(map->window->mlx_ptr);
// }

void cleanup_resources(t_map *map)
{
	release_map_memory(map);
	mlx_destroy_image(map->window->mlx_ptr, map->data->img);
	mlx_destroy_window(map->window->mlx_ptr, map->window->win_ptr);
#ifdef __linux__
	mlx_destroy_display(map->window->mlx_ptr);
#endif
	free(map->window->mlx_ptr);
}

int handle_window_close(t_map *map)
{
	cleanup_resources(map);
	exit(0);
}

void release_texture_paths(t_map *map)
{
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
}

void cleanup_map_and_textures(t_map *map)
{
	int idx;

	idx = 0;
	if (map->map)
	{
		while (map->map[idx])
		{
			free(map->map[idx]);
			idx++;
		}
		free(map->map);
	}
	if (map->ea_texture_img.img != NULL)
		mlx_destroy_image(map->window->mlx_ptr, map->ea_texture_img.img);
	if (map->no_texture_img.img != NULL)
		mlx_destroy_image(map->window->mlx_ptr, map->no_texture_img.img);
	if (map->we_texture_img.img != NULL)
		mlx_destroy_image(map->window->mlx_ptr, map->we_texture_img.img);
	if (map->so_texture_img.img != NULL)
		mlx_destroy_image(map->window->mlx_ptr, map->so_texture_img.img);
}

void release_map_memory(t_map *map)
{
	release_texture_paths(map);
	cleanup_map_and_textures(map);
}
