/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:15 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 13:01:17 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void err(char *str, t_map *map)
{
	printf("Error: %s \n", str);
	free_map(map);
	exit(1);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		*(unsigned int *)dst = color;
	}
}

t_data create_img(char *path, t_map *map)
{
	t_data img;
	int width;
	int height;

	width = TEXTURE_SIZE;
	height = TEXTURE_SIZE;
	img.img = mlx_xpm_file_to_image(map->window->mlx_ptr, path, &width,
									&height);
	if (!img.img || !*path)
	{
		printf("Error: Failed to load the image\n");
		ft_close_win(map);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	if (!img.addr)
	{
		printf("Error: Failed to load the image\n");
		ft_close_win(map);
	}
	return (img);
}

int get_pixel(t_data *img, int x, int y)
{
	char *dst;

	if (x < 0 || x >= TEXTURE_SIZE || y < 0 || y >= TEXTURE_SIZE)
	{
		fprintf(stderr, "Attempted to access pixel out of bounds.\n");
		return (0);
	}
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void load_textures(t_map *map)
{
	map->no_texture_img = create_img(map->no_texture, map);
	map->so_texture_img = create_img(map->so_texture, map);
	map->we_texture_img = create_img(map->we_texture, map);
	map->ea_texture_img = create_img(map->ea_texture, map);
}
