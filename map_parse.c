#include "so_long.h"
#include <stdio.h>
int get_size(char *filename, t_game *game)
{
    int height;
    char *rows;
    int fd;

    height = 0;
    fd = open(filename, O_RDONLY);
    if(fd < 0)
        return 0;
    rows = get_next_line(fd);
    game->width = map_rowlen(rows);
    while (rows && ++height > 0)
    {
        free(rows);
        rows = get_next_line(fd);
        if(!rows)
            return height;
        if(map_rowlen(rows) != game->width)
            return (-1);
    }
    close(fd);
    return (height);
}

int    map_process(char **map, char *filename, t_game *game)
{
    int j;
    int fd;
    char *line;
    int i;

    j = 0;
    i = 0;
    fd = open(filename, O_RDONLY);
    if(fd < 0)
        return 0;
    while(j < game->height)
    {
        line = get_next_line(fd);
        line[map_rowlen(line)] = '\0';
        map[j] = line;
        j++;
    }
    map[j] = NULL;
    close(fd);
    return 1;
}

char **parse_map(char *filename, t_game *game)
{
    char **map;

    game->height = get_size(filename, game);
    if(game->height <= 0)
    {   
        game->height == 0 ? perror("Map is empty. ") : perror("Map is not rectangle. ");
        return (NULL);       
    }
    map = (char **)malloc(sizeof(char *) * (game->height + 1));
    printf("%d %d", game->width, game->height);
    if(!map)
        return (NULL);
    map_process(map, filename, game);
    return map;
}
