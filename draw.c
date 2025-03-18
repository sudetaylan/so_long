#include "so_long.h"

static void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * game->tile_size,
		y * game->tile_size);
}

static void	draw_image(t_game *game, int x, int y)
{
	char	current;

	put_image(game, game->floor_img, x, y);
	current = game->map[y][x];
	if (current == '1')
		put_image(game, game->wall_img, x, y);
	if (current == 'C')
		put_image(game, game->collect_img, x, y);
	if (current == 'E')
		put_image(game, game->exit_img, x, y);
	if (x == game->player_x && y == game->player_y)
		put_image(game, game->player_img, x, y);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_image(game, x, y);
			x++;
		}
		y++;
	}
}