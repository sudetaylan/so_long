#include "so_long.h"
#include <stdio.h>
int	close_win(t_game *game)
{
	close_game(game);
	exit(0);
	return (0);
}
static int	check_win(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E'
		&& (game->collected == game->collect_count))
	{
		write(1, "Success! You escaped!\n", 22);
		close_game(game);
		exit(0);
	}
	return (0);
}

static void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map[new_y][new_x] = '0';
	}
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_putnbr(game->moves);
	check_win(game, new_x, new_y);
}
int	handle_movements(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		close_game(game);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	draw_map(game);
	return (0);
}