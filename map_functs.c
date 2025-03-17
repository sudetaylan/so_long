#include "so_long.h"

int map_rowlen(char *row)
{
    int i;

    i = 0;
    while (row[i] != '\0' && row[i] != '\n')
        i++;
    return i;
}

int arg_check(char *str, char *p)
{
    int i;

    i = map_rowlen(str) - 4;
    while(str[i])
    {
        if(str[i++] != *p++)
            return 0;
    }
    return 1;
}
