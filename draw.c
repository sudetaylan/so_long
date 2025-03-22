/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:54:16 by staylan           #+#    #+#             */
/*   Updated: 2025/03/22 17:54:49 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * game->tile_size,
		y * game->tile_size);
}

static void	draw_image(t_game *game, int col, int row, char element)
{
	put_image(game, game->floor_img, col, row);
	if (element == '1')
		put_image(game, game->wall_img, col, row);
	if (element == 'C')
		put_image(game, game->collect_img, col, row);
	if (element == 'E')
		put_image(game, game->exit_img, col, row);
	if (col == game->player_x && row == game->player_y)
		put_image(game, game->player_img, col, row);
}

void	draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->height)
	{
		col = 0;
		while (col < game->width)
		{
			draw_image(game, col, row, game->map[row][col]);
			col++;
		}
		row++;
	}
}
