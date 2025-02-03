/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:06 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:19:00 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *extract_identifier_value(char *source_line, char *identifier)
{
	char *line_start;
	int identifier_length;

	if (!source_line || !identifier)
		return (NULL);
	line_start = source_line;
	identifier_length = ft_strlen(identifier);

	// Skip leading whitespace
	while (*source_line && ft_isspace(*source_line))
		source_line++;

	// Check if line starts with identifier
	if (source_line == line_start && 
		ft_strncmp(source_line, identifier, identifier_length) == 0 && 
		(source_line[identifier_length] == '\0' || 
		 ft_isspace(source_line[identifier_length])))
	{
		source_line += ft_strlen(identifier);
		while (*source_line && ft_isspace(*source_line))
			source_line++;
		if (source_line[ft_strlen(source_line) - 1] == '\n')
			source_line[ft_strlen(source_line) - 1] = '\0';
		return (source_line);
	}
	return (NULL);
}

void process_map_line(t_map *map, char **map_buffer, char *line)
{
	char *temp_buffer;

	if (map->ceiling_color != NULL && !is_blank(line))
	{
		temp_buffer = *map_buffer;
		*map_buffer = ft_strjoin(temp_buffer, line);
		free(temp_buffer);
	}
	initialize_map_config(line, map);
	free(line);
}

void read_and_process_map(int file_descriptor, t_map *map)
{
	char *current_line;
	char *map_buffer;

	current_line = get_next_line(file_descriptor);
	map_buffer = ft_strdup("");
	while (current_line != NULL)
	{
		process_map_line(map, &map_buffer, current_line);
		current_line = get_next_line(file_descriptor);
	}
	validate_map_elements(map, map_buffer);

	if (*map_buffer != '\0')
		map->map = ft_split(map_buffer, '\n');
	else
	{
		free(map_buffer);
		handle_error("Empty map", map);
	}
	free(map_buffer);
	close(file_descriptor);
}

void validate_map_character(t_map *map, t_player *player, int row, int col)
{
	char current_char;

	current_char = map->map[row][col];
	if (current_char == '1' || current_char == ' ' || current_char == '0')
		return;
	else if (current_char == 'N' || current_char == 'S' || 
			 current_char == 'W' || current_char == 'E')
	{
		if (player->p_direction != '\0')
			handle_error("Player was already defined", map);
		player->x = col + 0.5;
		player->y = row + 0.5;
		player->p_direction = current_char;
	}
	else
		handle_error("Invalid map", map);
}

void validate_map_structure(t_map *map, t_player *player)
{
	int row;
	int col;

	row = 0;
	player->p_direction = '\0';
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			validate_map_character(map, player, row, col);
			col++;
		}
		row++;
	}

	// Validate map requirements
	if (player->p_direction == '\0')
		handle_error("Player was not defined", map);
	if (!validate_map_closure(map->map))
		handle_error("Map is not closed", map);

	// Parse color values
	map->ceiling_color_int = parse_rgb_color(map->ceiling_color, map);
	map->floor_color_int = parse_rgb_color(map->floor_color, map);
}
