#include "so_long.h"
int map_rowlen(char *row)
{
    int i;

    i = 0;
    while (row[i] != '\0' && row[i] != '\n')
        i++;
    return i;
}

void    clean_rows(char *line)
{
	int	len;

	len = map_rowlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}