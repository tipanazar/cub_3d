/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:26 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 12:59:28 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_clear_all(t_map *map)
// {
// 	free_map(map);
// 	mlx_destroy_image(map->window->mlx_ptr, map->data->img);
// 	mlx_destroy_window(map->window->mlx_ptr, map->window->win_ptr);
// 	mlx_destroy_display(map->window->mlx_ptr);
// 	free(map->window->mlx_ptr);
// }

void ft_clear_all(t_map *map)
{
	free_map(map);
	mlx_destroy_image(map->window->mlx_ptr, map->data->img);
	mlx_destroy_window(map->window->mlx_ptr, map->window->win_ptr);
#ifdef __linux__
	mlx_destroy_display(map->window->mlx_ptr);
#endif
	free(map->window->mlx_ptr);
}

int ft_close_win(t_map *map)
{
	ft_clear_all(map);
	exit(0);
}

void free_textures_and_colors(t_map *map)
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

void free_map_and_images(t_map *map)
{
	int i;

	i = 0;
	if (map->map)
	{
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
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

void free_map(t_map *map)
{
	free_textures_and_colors(map);
	free_map_and_images(map);
}
