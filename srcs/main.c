/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:59:47 by nkarpeko          #+#    #+#             */
/*   Updated: 2025/02/03 02:17:38 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_map map;
	t_player player;
	t_data data;
	t_window window;
	t_rcst rcst;

	map.player = &player;
	map.data = &data;
	map.window = &window;
	map.rcst = &rcst;
	if (ac == 2)
	{
		initialize_game_state(&map);
		setup_map_from_file(av[1], &map);
		validate_map_structure(&map, &player);
		initialize_game_window(&map);
		release_map_memory(&map);
	}
	else
		printf("Error: Invalid number of arguments\n");
	return (0);
}
