/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:35:03 by staylan           #+#    #+#             */
/*   Updated: 2025/03/23 17:42:13 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_height(const char *filename)
{
	int		fd;
	int		height;
	char	buffer[1];
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

static int	map_process(char **map, int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (map[i] = NULL, 0);
		clean_newline(line);
		map[i] = line;
		if (i == 0)
			game->width = map_rowlen(map[0]);
		i++;
	}
	map[i] = NULL;
	i = 0;
	while (i < game->height)
	{
		if (!check_line_width(map, i, game->width))
			return (0);
		i++;
	}
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
		return (NULL);
	}
	map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	if (!map_process(map, fd, game))
	{
		free_map(map, game->height);
		perror("Map is not rectangle.");
		close(fd);
		return (0);
	}
	close(fd);
	return (map);
}
