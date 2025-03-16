#include "so_long.h"
static void init_param(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->item_count = 0;
	game->i_collected = 0;
	game->moves = 0;
	game->tile_size = 64;
}

int   map_last(char *path, t_game *game)
{
    game->map = parse_map(path, game);
    if(!game->map)
        return 0;
    if(!check_map(game))
        return 0;
    return 1;
}
int main(int argc, char **argv)
{
    t_game game;

    init_param(&game);
    if(argc != 2)
        perror("Usage : ./so_long ./maps/Your map choice. ");
    if(!map_last(argv[1], &game))
        return 0;  
}
