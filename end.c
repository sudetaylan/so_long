/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:29:10 by staylan           #+#    #+#             */
/*   Updated: 2025/03/22 17:31:35 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (i < height && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (1);
}

int	close_game(t_game *game)
{
	if (game->win)
	{
		if (game->wall_img)
			mlx_destroy_image(game->mlx, game->wall_img);
		if (game->player_img)
			mlx_destroy_image(game->mlx, game->player_img);
		if (game->exit_img)
			mlx_destroy_image(game->mlx, game->exit_img);
		if (game->collect_img)
			mlx_destroy_image(game->mlx, game->collect_img);
		if (game->floor_img)
			mlx_destroy_image(game->mlx, game->floor_img);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->map)
		free_map(game->map, game->height);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}

int	close_win(t_game *game)
{
	close_game(game);
	exit(0);
}
