static char *read_line(int fd)
{
char buffer[BUFFER_SIZE + 1];
char *line;
char *temp;
int bytes_read;
// Allocate initial empty string
line = malloc(sizeof(char));
if (!line)
return NULL;
line[0] = '\0';
// Read until newline or EOF
while (1)
 {
bytes_read = read(fd, buffer, BUFFER_SIZE);
// Error or EOF
if (bytes_read <= 0)
 {
if (bytes_read < 0 || line[0] == '\0')
 {
free(line);
return NULL;
 }
return line;
 }
buffer[bytes_read] = '\0';
// Check for newline
int newline_pos = -1;
for (int i = 0; i < bytes_read; i++)
 {
if (buffer[i] == '\n')
 {
newline_pos = i;
break;
 }
 }
if (newline_pos >= 0)
 {
// Found newline - truncate buffer at newline + 1
buffer[newline_pos + 1] = '\0';
 }
// Join line and buffer
temp = malloc(ft_strlen(line) + ft_strlen(buffer) + 1);
if (!temp)
 {
free(line);
return NULL;
 }
// Copy line to temp
strcpy(temp, line);
// Append buffer to temp
strcat(temp, buffer);
free(line);
line = temp;
if (newline_pos >= 0)
break; // We found a newline, so we can stop reading
 }
return line;
}
static int map_process(char **map, int fd, t_game *game)
{
    char *line;
    int i;
    
    i = 0;
    while (i < game->height)
    {
        line = read_line(fd);
        if (!line)
        {
            free_map(map, i);
            return 0;
        }
		clean_newline(line);
        map[i] = ft_strdup(line);
        if (!map[i])
        {
            free(line);
            free_map(map, i);
            return 0;
        }
        free(line);
        game->width = ft_strlen(map[0]);
        if (i > 0 && (int)ft_strlen(map[i]) != game->width)
        {
            free_map(map, i + 1);
            return 0;
        }
        i++;
    }
    map[i] = NULL;
    return 1;
}
