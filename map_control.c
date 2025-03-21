#include "so_long.h"
int check_map(t_game *game)
{
    int exit;
    int collectable;
    int player;

    exit = 0;
    collectable = 0;
    player = 0;
    if(!control_elements(game, &exit, &collectable, &player))
    {
        write(1, "Error\nInvalid map: Map must consist 0, 1, P, E, C only. ", 57);
        return 0;      
    }
    if(!control_walls(game))
    {
        write(1, "Error\nInvalid map: Map must be surrounded by walls. ", 53);
        return 0;     
    }
    if(player != 1 || exit != 1 || collectable < 1)
    {
        write(1, "Error\nInvalid map: Number of elements are wrong. ", 50);
        return 0;      
    }
    game->collect_count = collectable;
	return (1);
}
int control_elements(t_game *game, int *exit, int *collectable,int *player)
{
	int		x;
	int		y;

	x = -1;
	while (++x < game->height)
	{
		y = -1;
		while (++y < game->width)
		{
			if (game->map[x][y] == 'P')
			{
				(*player)++;
				game->player_x = y;
				game->player_y = x;
			}
			else if (game->map[x][y] == 'E')
				(*exit)++;
			else if (game->map[x][y] == 'C')
				(*collectable)++;
			else if (game->map[x][y] != '0' && game->map[x][y] != '1')
				return (0);
		}
	}
	return (1);
}
int control_walls(t_game *game)
{
    int rows;
    int cols;

    rows = 0;
    while(rows < game->height)
    {
        cols = 0;
        if(rows == 0 || rows == (game->height - 1))
        {
            while(game->map[rows][cols] == '1')
                cols++;
            if(cols != game->width)
                return 0;
        }
        else if(game->map[rows][0] != '1' || game->map[rows][game->width - 1] != '1')
            return 0;
        rows++;
    }
    return 1;
}
