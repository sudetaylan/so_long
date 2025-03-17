#include "so_long.h"
int copy_map(t_game *game, char ***game_map)
{
    int i;

    i = 0;
    *game_map = (char **)malloc(sizeof(char *) * (game->height + 1));
    if(!game_map)
        return 0;
    while(i++ < game->height)
    {
        *game_map[i] = ft_strdup(game->map[i]);
        if(!(*game_map[i]))
        {
            while(--i >= 0)
                free(game_map[i]);
            free(*game_map);
            return 0;
        }
    }
    *game_map[game->height] = NULL;
    return (1); 
}
void flood_fill(char ***game_map, int p_x, int p_y, t_game *game)
{
    if(p_x < 0 || p_x > game->width || p_y < 0 || p_y > game->height)
        return ;
    if(*game_map[p_x][p_y] == '1' || *game_map[p_x][p_y] == 'X')
        return;
    *game_map[p_x][p_y] = 'X';
    flood_fill(game_map, p_x - 1, p_y, game);
    flood_fill(game_map, p_x + 1, p_y, game);
    flood_fill(game_map, p_x, p_y - 1, game);
    flood_fill(game_map, p_x, p_y + 1, game);
}
int compare_maps(char ***game_map, t_game *game)
{
    int i;
    int j;
    int c_flag;
    int e_flag;

    i = 0;
    c_flag = 0;
    e_flag = 0;
    while(i++ < game->height)
    {
        j = 0;
        while (j++ < game->width)
        {
            if(game->map[i][j] == 'C' && *game_map[i][j] == 'X')
                c_flag++;
            if(game->map[i][j] == 'E' && *game_map[i][j] == 'X')
                e_flag++;
        }
    }
    if(c_flag != game->item_count && e_flag != 1)
        return 0;
    return 1;
}
int	check_reachable(t_game *game)
{
    char **game_map;
	int		result;
	int		i;

	if (!copy_map(game, &game_map))
		return (0);
	flood_fill(&game_map, game->player_x, game->player_y, game);
	result = compare_maps(&game_map, game);
	i = 0;
	while (i < game->height)
		free(game_map[i++]);
	free(game_map);
	return (result);
}
