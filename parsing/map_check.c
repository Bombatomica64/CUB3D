/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:14:51 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/13 17:58:31 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	map_size(char *map_path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	i = 0;
	j++;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		err("Failed to open map file");
	while (get_next_line2(fd, &line) > 0)
	{
		if (line[0] != '1')
			j++;
		if (line[0] == '1')
			i++;
		free(line);
	}
	game->map_height = i;
	close(fd);
}

char	**parse_map(char *map_path, t_game *game)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;

	i = 0;
	map_size(map_path, game);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		err("Failed to open map file");
	map = malloc(sizeof(char *));
}
