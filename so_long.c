/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:49:41 by staylan           #+#    #+#             */
/*   Updated: 2025/03/22 21:22:09 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_param(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->collect_count = 0;
	game->collected = 0;
	game->moves = 0;
	game->tile_size = 64;
}

static int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(1, "Error\nmlx couldn't be initialized\n", 35);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->width * game->tile_size,
			game->height * game->tile_size, "so_long");
	if (!game->win)
	{
		write(1, "Error\nWindow couldn't be initialized\n", 38);
		return (0);
	}
	return (1);
}

static int	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->floor_img = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm",
			&w, &h);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", &w,
			&h);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm",
			&w, &h);
	game->collect_img = mlx_xpm_file_to_image(game->mlx,
			"./textures/collect.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "./textures/exit.xpm", &w,
			&h);
	if (!game->floor_img || !game->wall_img || !game->player_img
		|| !game->collect_img || !game->exit_img)
	{
		write(1, "Error\nTextures couldn't be loaded\n", 29);
		return (0);
	}
	return (1);
}

static int	map_all_controls(char *path, t_game *game)
{
	game->map = parse_map(path, game);
	if (!game->map || !check_map(game) || !check_reachable(game))
	{
		free_map(game->map, game->height);
		return (0);
	}
	if (!init_window(game) || !load_textures(game))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_param(&game);
	if (argc != 2 || !arg_check(argv[1], ".ber"))
	{
		write(1, "Usage : ./so_long ./maps/'file_name'.ber ", 42);
		return (0);
	}
	if (!map_all_controls(argv[1], &game))
	{
		write(1, "Error\nMap initilization is unsuccesfull", 40);
		return (0);
	}
	draw_map(&game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_key_hook(game.win, handle_movements, &game);
	mlx_loop(game.mlx);
	return (0);
}
