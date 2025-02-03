/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:01 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:14:25 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_frame(t_map *map)
{
	int screen_column;

	screen_column = 0;
	while (screen_column < WINDOW_WIDTH)
	{
		// Process each vertical line of the screen
		initialize_ray_parameters(map, screen_column);
		compute_ray_step_distances(map);
		execute_dda_raycast(map);
		calculate_projection_dimensions(map);
		compute_wall_texture_coordinates(map);
		render_wall_texture(map, screen_column);
		screen_column++;
	}
	// Display the rendered frame
	mlx_put_image_to_window(map->window->mlx_ptr, map->window->win_ptr,
							map->data->img, 0, 0);
}
