/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:31 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:19:17 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_color_component(char **color_str)
{
	int component_value;

	if (!ft_isdigit(**color_str))
		return (-1);
	component_value = ft_atoi(*color_str);
	while (ft_isdigit(**color_str))
		(*color_str)++;
	if (component_value < 0 || component_value > 255)
		return (-1);
	return (component_value);
}

int parse_rgb_color(char *color_str, t_map *map)
{
	int rgb_value;
	int red;
	int green;
	int blue;

	while (*color_str == ' ')
		color_str++;
	red = parse_color_component(&color_str);
	if (*color_str != ',')
		handle_error("Color should be R,G,B\n", map);
	color_str++;
	green = parse_color_component(&color_str);
	if (*color_str != ',')
		handle_error("Color should be R,G,B\n", map);
	color_str++;
	blue = parse_color_component(&color_str);
	while (*color_str == ' ')
		color_str++;
	if (*color_str != '\0' || red == -1 || green == -1 || blue == -1)
		handle_error("Color should be R,G,B\n", map);
	rgb_value = (red << 16 | green << 8 | blue);
	return (rgb_value);
}

void render_background(t_map *map)
{
	int width;
	int height;

	height = 0;
	while (height < WINDOW_HEIGHT)
	{
		width = 0;
		while (width < WINDOW_WIDTH)
		{
			if (height < WINDOW_HEIGHT / 2)
				draw_pixel(map->data, width, height, map->ceiling_color_int);
			else
				draw_pixel(map->data, width, height, map->floor_color_int);
			width++;
		}
		height++;
	}
	mlx_put_image_to_window(map->window->mlx_ptr, map->window->win_ptr,
							map->data->img, 0, 0);
}
