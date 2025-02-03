/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:15 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:18:19 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_error(char *error_message, t_map *map)
{
	printf("Error: %s \n", error_message);
	release_map_memory(map);
	exit(1);
}

void draw_pixel(t_data *buffer, int pos_x, int pos_y, int color)
{
	char *pixel_address;

	pixel_address = buffer->addr + (pos_y * buffer->line_length + 
								  pos_x * (buffer->bits_per_pixel / 8));
	if (pos_x >= 0 && pos_x < WINDOW_WIDTH && pos_y >= 0 && pos_y < WINDOW_HEIGHT)
	{
		*(unsigned int *)pixel_address = color;
	}
}

t_data load_texture_image(char *texture_path, t_map *map)
{
	t_data texture;
	int texture_width;
	int texture_height;

	texture_width = TEXTURE_SIZE;
	texture_height = TEXTURE_SIZE;
	texture.img = mlx_xpm_file_to_image(map->window->mlx_ptr, texture_path, 
									   &texture_width, &texture_height);
	if (!texture.img || !*texture_path)
	{
		printf("Error: Failed to load the image\n");
		handle_window_close(map);
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, 
									&texture.line_length, &texture.endian);
	if (!texture.addr)
	{
		printf("Error: Failed to load the image\n");
		handle_window_close(map);
	}
	return (texture);
}

int get_texture_pixel(t_data *texture, int tex_x, int tex_y)
{
	char *pixel_address;

	if (tex_x < 0 || tex_x >= TEXTURE_SIZE || tex_y < 0 || tex_y >= TEXTURE_SIZE)
	{
		fprintf(stderr, "Attempted to access pixel out of bounds.\n");
		return (0);
	}
	pixel_address = texture->addr + (tex_y * texture->line_length + 
								   tex_x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel_address);
}

void initialize_textures(t_map *map)
{
	map->no_texture_img = load_texture_image(map->no_texture, map);
	map->so_texture_img = load_texture_image(map->so_texture, map);
	map->we_texture_img = load_texture_image(map->we_texture, map);
	map->ea_texture_img = load_texture_image(map->ea_texture, map);
}
