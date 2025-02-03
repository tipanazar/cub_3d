/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:10 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:19:53 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int update_game_state(t_map *map)
{
	update_player_state(map);
	return (0);
}

void initialize_player_vectors(t_player *player, int direction_x, int direction_y)
{
	player->pdx = direction_x;
	player->pdy = direction_y;
}

void initialize_camera_plane(t_player *player, double plane_x, double plane_y)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void setup_player_orientation(t_player *player)
{
	if (player->p_direction == 'N')
	{
		initialize_player_vectors(player, 0, -1);
		initialize_camera_plane(player, 0.66, 0);
	}
	else if (player->p_direction == 'S')
	{
		initialize_player_vectors(player, 0, 1);
		initialize_camera_plane(player, -0.66, 0);
	}
	else if (player->p_direction == 'E')
	{
		initialize_player_vectors(player, 1, 0);
		initialize_camera_plane(player, 0, 0.66);
	}
	else if (player->p_direction == 'W')
	{
		initialize_player_vectors(player, -1, 0);
		initialize_camera_plane(player, 0, -0.66);
	}
}

void initialize_game_window(t_map *map)
{
	map->window->mlx_ptr = mlx_init();
	map->window->win_ptr = mlx_new_window(map->window->mlx_ptr, WINDOW_WIDTH,
										  WINDOW_HEIGHT, "Cub3D");
	map->data->img = mlx_new_image(map->window->mlx_ptr, WINDOW_WIDTH,
								   WINDOW_HEIGHT);
	map->data->addr = mlx_get_data_addr(map->data->img,
										&map->data->bits_per_pixel, &map->data->line_length,
										&map->data->endian);
	initialize_textures(map);
	setup_player_orientation(map->player);
	mlx_hook(map->window->win_ptr, 2, 1L << 0, handle_keypress, map);
	mlx_hook(map->window->win_ptr, 3, 1L << 1, handle_keyrelease, map);
	mlx_hook(map->window->win_ptr, 17, 0, handle_window_close, map);
	mlx_loop_hook(map->window->mlx_ptr, update_game_state, map);
	mlx_loop(map->window->mlx_ptr);
}
