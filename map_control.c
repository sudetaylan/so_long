/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:24:15 by staylan           #+#    #+#             */
/*   Updated: 2025/03/22 21:09:32 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	control_elements(t_game *game, int *player, int *exit, int *collect)
{
	int	row;
	int	col;

	row = -1;
	while (++row < game->height)
	{
		col = -1;
		while (++col < game->width)
		{
			if (game->map[row][col] == 'P')
			{
				(*player)++;
				game->player_x = col;
				game->player_y = row;
			}
			else if (game->map[row][col] == 'E')
				(*exit)++;
			else if (game->map[row][col] == 'C')
				(*collect)++;
			else if (game->map[row][col] != '0' && game->map[row][col] != '1')
				return (0);
		}
	}
	return (1);
}

static int	control_walls(t_game *game)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < game->height)
	{
		cols = 0;
		if (rows == 0 || rows == (game->height - 1))
		{
			while (game->map[rows][cols] == '1')
				cols++;
			if (cols != game->width)
				return (0);
		}
		else if (game->map[rows][0] != '1' ||
					game->map[rows][game->width - 1] != '1')
			return (0);
		rows++;
	}
	return (1);
}

int	check_map(t_game *game)
{
	int	exit;
	int	collect;
	int	player;

	exit = 0;
	collect = 0;
	player = 0;
	if (!control_elements(game, &player, &exit, &collect))
	{
		write(1, "Error\nMap must consist of 0, 1, P, E, C only. ", 57);
		return (0);
	}
	if (!control_walls(game))
	{
		write(1, "Error\nInvalid map: Map must be surrounded by walls. ", 53);
		return (0);
	}
	if (player != 1 || exit != 1 || collect < 1)
	{
		write(1, "Error\nInvalid map: Number of elements are wrong. ", 50);
		return (0);
	}
	game->collect_count = collect;
	return (1);
}
