/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:31 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 12:59:33 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_and_parse_number(char **str)
{
	int value;

	if (!ft_isdigit(**str))
		return (-1);
	value = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int get_the_color(char *str, t_map *map)
{
	int color;
	int r;
	int g;
	int b;

	while (*str == ' ')
		str++;
	r = validate_and_parse_number(&str);
	if (*str != ',')
		err("Color should be R,G,B\n", map);
	str++;
	g = validate_and_parse_number(&str);
	if (*str != ',')
		err("Color should be R,G,B\n", map);
	str++;
	b = validate_and_parse_number(&str);
	while (*str == ' ')
		str++;
	if (*str != '\0' || r == -1 || g == -1 || b == -1)
		err("Color should be R,G,B\n", map);
	color = (r << 16 | g << 8 | b);
	return (color);
}

void clear_screen(t_map *map)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(map->data, x, y, map->ceiling_color_int);
			else
				my_mlx_pixel_put(map->data, x, y, map->floor_color_int);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->window->mlx_ptr, map->window->win_ptr,
							map->data->img, 0, 0);
}
