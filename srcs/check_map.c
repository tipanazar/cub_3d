/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:09 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 12:59:12 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_path(char *file, t_map *map)
{
	char **splitted_path;
	int arr_idx;

	splitted_path = ft_split(file, '.');
	arr_idx = 0;
	while (splitted_path[arr_idx])
		arr_idx++;
	if (ft_strncmp(splitted_path[arr_idx - 1], "cub", 4))
	{
		ft_free_char_arr(splitted_path);
		err("Map file is not .cub", map);
	}
	ft_free_char_arr(splitted_path);
}

void check_textures_and_colors(t_map *map, char *holder_map)
{
	if (map->no_texture == NULL || map->so_texture == NULL || map->we_texture == NULL || map->ea_texture == NULL)
	{
		free(holder_map);
		err("Texture is not defined", map);
	}
	if (map->floor_color == NULL || map->ceiling_color == NULL)
	{
		free(holder_map);
		err("Color is not defined", map);
	}
}

bool is_cell_closed(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1] || map[i - 1][j] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i][j + 1] == ' ' || map[i - 1][j - 1] == ' ' || map[i + 1][j + 1] == ' ' || map[i - 1][j + 1] == ' ' || map[i + 1][j - 1] == ' ' || map[i - 1][j] == '\0' || map[i][j - 1] == '\0' || map[i + 1][j] == '\0' || map[i][j + 1] == '\0' || map[i - 1][j - 1] == '\0' || map[i + 1][j + 1] == '\0' || map[i - 1][j + 1] == '\0' || map[i + 1][j - 1] == '\0')
		return (false);
	return (true);
}

bool is_map_closed(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E') && !is_cell_closed(map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
