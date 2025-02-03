/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:09 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:19:00 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void validate_file_extension(char *filename, t_map *map)
{
	char **extension_parts;
	int part_count;

	extension_parts = ft_split(filename, '.');
	part_count = 0;
	while (extension_parts[part_count])
		part_count++;
	if (ft_strncmp(extension_parts[part_count - 1], "cub", 4))
	{
		ft_free_char_arr(extension_parts);
		handle_error("Map file is not .cub", map);
	}
	ft_free_char_arr(extension_parts);
}

void validate_map_elements(t_map *map, char *raw_map_data)
{
	if (!map->no_texture || !map->so_texture || 
		!map->we_texture || !map->ea_texture)
	{
		free(raw_map_data);
		handle_error("Texture is not defined", map);
	}
	if (!map->floor_color || !map->ceiling_color)
	{
		free(raw_map_data);
		handle_error("Color is not defined", map);
	}
}

bool validate_cell_boundaries(char **grid, int row, int col)
{
	bool is_border = (row == 0 || col == 0 || !grid[row + 1] || !grid[row][col + 1]);
	bool has_adjacent_space = (grid[row - 1][col] == ' ' || grid[row][col - 1] == ' ' ||
							 grid[row + 1][col] == ' ' || grid[row][col + 1] == ' ');
	bool has_diagonal_space = (grid[row - 1][col - 1] == ' ' || grid[row + 1][col + 1] == ' ' ||
							 grid[row - 1][col + 1] == ' ' || grid[row + 1][col - 1] == ' ');
	bool has_null_adjacent = (grid[row - 1][col] == '\0' || grid[row][col - 1] == '\0' ||
							grid[row + 1][col] == '\0' || grid[row][col + 1] == '\0');
	bool has_null_diagonal = (grid[row - 1][col - 1] == '\0' || grid[row + 1][col + 1] == '\0' ||
							grid[row - 1][col + 1] == '\0' || grid[row + 1][col - 1] == '\0');

	return !(is_border || has_adjacent_space || has_diagonal_space || 
			 has_null_adjacent || has_null_diagonal);
}

bool validate_map_closure(char **grid)
{
	int row;
	int col;
	char current_cell;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			current_cell = grid[row][col];
			if ((current_cell == '0' || current_cell == 'N' || 
				 current_cell == 'S' || current_cell == 'W' || 
				 current_cell == 'E') && !validate_cell_boundaries(grid, row, col))
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}
