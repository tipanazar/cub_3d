/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpeko <nkarpeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:06 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/01/29 13:01:07 by nkarpeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *save_the_line(char *line, char *to_find)
{
	char *original_line;
	int to_find_len;

	if (!line || !to_find)
		return (NULL);
	original_line = line;
	to_find_len = ft_strlen(to_find);
	while (*line && ft_isspace(*line))
		line++;
	if (line == original_line && ft_strncmp(line, to_find, to_find_len) == 0 && (line[to_find_len] == '\0' || ft_isspace(line[to_find_len])))
	{
		line += ft_strlen(to_find);
		while (*line && ft_isspace(*line))
			line++;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		return (line);
	}
	return (NULL);
}

void process_line(t_map *map, char **holder_map, char *line)
{
	char *temp;

	if (map->ceiling_color != NULL && !is_blank(line))
	{
		temp = *holder_map;
		*holder_map = ft_strjoin(temp, line);
		free(temp);
	}
	map_init(line, map);
	free(line);
}

void process_map_lines(int fd, t_map *map)
{
	char *line;
	char *holder_map;

	line = get_next_line(fd);
	holder_map = ft_strdup("");
	while (line != NULL)
	{
		process_line(map, &holder_map, line);
		line = get_next_line(fd);
	}
	check_textures_and_colors(map, holder_map);
	if (*holder_map != '\0')
		map->map = ft_split(holder_map, '\n');
	else
	{
		free(holder_map);
		err("Empty map", map);
	}
	free(holder_map);
	close(fd);
}

void process_map_symbol(t_map *map, t_player *player, int i, int j)
{
	if (map->map[i][j] == '1' || map->map[i][j] == ' ' || map->map[i][j] == '0')
	{
	}
	else if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E')
	{
		if (player->p_direction != '\0')
			err("Player was already defined", map);
		player->x = j + 0.5;
		player->y = i + 0.5;
		player->p_direction = map->map[i][j];
	}
	else
		err("Invalid map", map);
}

void map_validation(t_map *map, t_player *player)
{
	int i;
	int j;

	i = 0;
	player->p_direction = '\0';
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			process_map_symbol(map, player, i, j);
			j++;
		}
		i++;
	}
	if (player->p_direction == '\0')
		err("Player was not defined", map);
	if (!is_map_closed(map->map))
		err("Map is not closed", map);
	map->ceiling_color_int = get_the_color(map->ceiling_color, map);
	map->floor_color_int = get_the_color(map->floor_color, map);
}
