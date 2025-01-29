/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:38 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 12:59:40 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_init(char *str, t_map *map)
{
	char *saved_line;
	char *directions[6];
	char **textures[6];
	int i;

	directions[0] = "NO";
	directions[1] = "SO";
	directions[2] = "WE";
	directions[3] = "EA";
	directions[4] = "F";
	directions[5] = "C";
	textures[0] = &map->no_texture;
	textures[1] = &map->so_texture;
	textures[2] = &map->we_texture;
	textures[3] = &map->ea_texture;
	textures[4] = &map->floor_color;
	textures[5] = &map->ceiling_color;
	i = 0;
	while (i < 6)
	{
		saved_line = save_the_line(str, directions[i]);
		if (saved_line != NULL)
			set_texture(textures[i], saved_line, map);
		i++;
	}
}

void set_texture(char **texture, char *saved_line, t_map *map)
{
	if (saved_line != NULL)
	{
		if (*texture == NULL)
			*texture = ft_strdup(saved_line);
		else
			err("texture is already defined", map);
	}
}

void init_map_data(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->map = NULL;
}

void open_and_init_map(char *file, t_map *map)
{
	int fd;

	init_map_data(map);
	check_path(file, map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		err("Invalid file", map);
	process_map_lines(fd, map);
}

void init(t_map *map)
{
	map->ea_texture_img.img = NULL;
	map->we_texture_img.img = NULL;
	map->no_texture_img.img = NULL;
	map->so_texture_img.img = NULL;
	map->player->moving_forward = 0;
	map->player->moving_backward = 0;
	map->player->moving_left = 0;
	map->player->moving_right = 0;
	map->player->rotating_left = 0;
	map->player->rotating_right = 0;
}
