/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:35:03 by staylan           #+#    #+#             */
/*   Updated: 2025/03/22 22:13:53 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_height(const char *filename)
{
	int		fd;
	int		height;
	char	buffer[2];
	int		read_bytes;

	height = 1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, 1);
		if (read_bytes > 0 && buffer[0] == '\n')
			height++;
	}
	if (read_bytes == 0 && height == 0)
		height = 1;
	close(fd);
	return (height);
}

static int	check_line_width(char **map, int i, int width)
{
	if (i == 0)
		return (1);
	if (map_rowlen(map[i]) != width)
		return (0);
	return (1);
}

static void	clean_newline(char *line)
{
	int	len;

	len = map_rowlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	map_process(char **map, int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		if (!line)
			return(map[i] = NULL, 0);
		clean_newline(line);
		map[i] = ft_strdup(line);
		free(line);
		game->width = ft_strlen(map[0]);	
		if (!check_line_width(map, i, game->width))
		{
			free_map(map, i);
			return (0);			
		}
		i++;
	}	
	map[i] = NULL;
	free_map(map, i);
	return (1);
}

char	**parse_map(char *filename, t_game *game)
{
	char	**map;
	int		fd;

	game->height = get_height(filename);
	if (game->height == 0)
	{
		perror("Map is empty.");
	}
	map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!map_process(map, fd, game))
	{
		perror("Map is not rectangle. ");
		close(fd);
		return (0);
	}
	close(fd);
	return (map);
}
