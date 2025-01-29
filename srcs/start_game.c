/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:10 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 13:01:12 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int game_loop(t_map *map)
{
	update_player(map);
	return (0);
}

void set_player_direction(t_player *player, int pdx, int pdy)
{
	player->pdx = pdx;
	player->pdy = pdy;
}

void set_player_plane(t_player *player, double plane_x, double plane_y)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void initialize_player_direction(t_player *player)
{
	if (player->p_direction == 'N')
	{
		set_player_direction(player, 0, -1);
		set_player_plane(player, 0.66, 0);
	}
	else if (player->p_direction == 'S')
	{
		set_player_direction(player, 0, 1);
		set_player_plane(player, -0.66, 0);
	}
	else if (player->p_direction == 'E')
	{
		set_player_direction(player, 1, 0);
		set_player_plane(player, 0, 0.66);
	}
	else if (player->p_direction == 'W')
	{
		set_player_direction(player, -1, 0);
		set_player_plane(player, 0, -0.66);
	}
}

void game_start(t_map *map)
{
	map->window->mlx_ptr = mlx_init();
	map->window->win_ptr = mlx_new_window(map->window->mlx_ptr, WINDOW_WIDTH,
										  WINDOW_HEIGHT, "Cub_3d");
	map->data->img = mlx_new_image(map->window->mlx_ptr, WINDOW_WIDTH,
								   WINDOW_HEIGHT);
	map->data->addr = mlx_get_data_addr(map->data->img,
										&map->data->bits_per_pixel, &map->data->line_length,
										&map->data->endian);
	load_textures(map);
	initialize_player_direction(map->player);
	mlx_hook(map->window->win_ptr, 2, 1L << 0, key_press_hook, map);
	mlx_hook(map->window->win_ptr, 3, 1L << 1, key_release_hook, map);
	mlx_hook(map->window->win_ptr, 17, 0, ft_close_win, map);
	mlx_loop_hook(map->window->mlx_ptr, game_loop, map);
	mlx_loop(map->window->mlx_ptr);
}
