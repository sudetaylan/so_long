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
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;

	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		item_count;
	int		i_collected;
	int		moves;

	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*collect_img;
	void	*exit_img;

	int		tile_size;
}			t_game;

int map_rowlen(char *row);
int get_size(char *filename, t_game *game);
int map_process(char **map, char *filename, t_game *game);
char **parse_map(char *filename, t_game *game);
int control_elements(t_game *game, int *exit, int *collectable,int *player);
int control_walls(t_game *game);
int   map_last(char *path, t_game *game);
int check_map(t_game *game);
int arg_check(char *str, char *p);
int	check_reachable(t_game *game);
int compare_maps(char ***game_map, t_game *game);
void flood_fill(char ***game_map, int p_x, int p_y, t_game *game);
int copy_map(t_game *game, char ***game_map);

#endif