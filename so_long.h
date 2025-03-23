/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:53:55 by staylan           #+#    #+#             */
/*   Updated: 2025/03/23 17:51:15 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "inc/gnl/get_next_line.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;

	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collect_count;
	int		collected;
	int		moves;

	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*collect_img;
	void	*exit_img;

	int		tile_size;
}			t_game;

int		map_rowlen(char *row);
char	**parse_map(char *filename, t_game *game);
int		check_map(t_game *game);
int		arg_check(char *str, char *p);
void	draw_map(t_game *game);
int		close_win(t_game *game);
int		close_game(t_game *game);
void	free_map(char **map, int height);
int		handle_movements(int keycode, t_game *game);
int		check_reachable(t_game *game);
void	ft_putnbr(int nb);
void	clean_newline(char *line);

#endif
