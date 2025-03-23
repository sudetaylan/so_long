/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reach_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:44:35 by staylan           #+#    #+#             */
/*   Updated: 2025/03/23 16:36:01 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	copy_map(t_game *game, char **game_map)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		game_map[i] = ft_strdup(game->map[i]);
		if (!(game_map)[i])
		{
			while (--i >= 0)
				free((game_map)[i]);
			free(game_map);
			return (0);
		}
		i++;
	}
	game_map[game->height] = NULL;
	return (1);
}

static void	flood_fill(char **game_map, int p_x, int p_y, t_game *game)
{
	if (p_x < 0 || p_x >= game->width || p_y < 0 || p_y >= game->height)
		return ;
	if (game_map[p_y][p_x] == '1' || game_map[p_y][p_x] == 'X')
		return ;
	game_map[p_y][p_x] = 'X';
	flood_fill(game_map, p_x - 1, p_y, game);
	flood_fill(game_map, p_x + 1, p_y, game);
	flood_fill(game_map, p_x, p_y - 1, game);
	flood_fill(game_map, p_x, p_y + 1, game);
}

static int	compare_maps(char **game_map, t_game *game)
{
	int	i;
	int	j;
	int	c_flag;
	int	e_flag;

	i = -1;
	c_flag = 0;
	e_flag = 0;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'C' && game_map[i][j] == 'X')
				c_flag++;
			if (game->map[i][j] == 'E' && game_map[i][j] == 'X')
				e_flag++;
		}
	}
	if (c_flag != game->collect_count || e_flag != 1)
		return (0);
	return (1);
}

int	check_reachable(t_game *game)
{
	char	**game_map;
	int		result;
	int		i;

	i = 0;
	game_map = malloc(sizeof(char *) * (game->height + 1));
	if (!game_map || (!copy_map(game, game_map)))
	{
		write(2, "Error\nMap couldn't be copied. ", 31);
		return (0);
	}
	flood_fill(game_map, game->player_x, game->player_y, game);
	result = compare_maps(game_map, game);
	if (result == 0)
	{
		write(2, "Error\nSome parts of map are not accessible.\n", 45);
	}
	while (i < game->height)
		free(game_map[i++]);
	free(game_map);
	return (result);
}
