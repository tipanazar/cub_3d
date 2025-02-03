/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:38 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:19:00 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void initialize_map_config(char *config_str, t_map *map)
{
	char *parsed_line;
	char *texture_identifiers[6];
	char **texture_pointers[6];
	int config_idx;

	texture_identifiers[0] = "NO";
	texture_identifiers[1] = "SO";
	texture_identifiers[2] = "WE";
	texture_identifiers[3] = "EA";
	texture_identifiers[4] = "F";
	texture_identifiers[5] = "C";
	texture_pointers[0] = &map->no_texture;
	texture_pointers[1] = &map->so_texture;
	texture_pointers[2] = &map->we_texture;
	texture_pointers[3] = &map->ea_texture;
	texture_pointers[4] = &map->floor_color;
	texture_pointers[5] = &map->ceiling_color;
	config_idx = 0;
	while (config_idx < 6)
	{
		parsed_line = extract_identifier_value(config_str, texture_identifiers[config_idx]);
		if (parsed_line != NULL)
			assign_texture(texture_pointers[config_idx], parsed_line, map);
		config_idx++;
	}
}

void assign_texture(char **texture_ptr, char *texture_data, t_map *map)
{
	if (texture_data != NULL)
	{
		if (*texture_ptr == NULL)
			*texture_ptr = ft_strdup(texture_data);
		else
			handle_error("texture is already defined", map);
	}
}

void initialize_map_pointers(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->map = NULL;
}

void setup_map_from_file(char *filename, t_map *map)
{
	int file_descriptor;

	initialize_map_pointers(map);
	validate_file_extension(filename, map);
	file_descriptor = open(filename, O_RDONLY);
	if (file_descriptor == -1)
		handle_error("Invalid file", map);
	read_and_process_map(file_descriptor, map);
}

void initialize_game_state(t_map *map)
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
