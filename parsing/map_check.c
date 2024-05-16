/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:14:51 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 10:43:09 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	file_size(char *map_path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		err("Failed to open map file");
	while (get_next_line2(fd, &line) > 0)
		i++;
	free(line);
	i++;
	game->input.file_len = i;
	close(fd);
}

char	**parse_map(char *map_path, t_game *game)
{
	int		fd;
	char	*line;
	char	**map_and_txt;
	int		i;

	i = 0;
	line = NULL;
	file_size(map_path, game);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		err("Failed to open map file");
	map_and_txt = malloc(sizeof(char *) * (game->input.file_len + 1));
	if (!map_and_txt)
		err("Failed to allocate map");
	while (get_next_line2(fd, &line) > 0)
	{
		map_and_txt[i] = ft_strdup(line);
		free(line);
		line = NULL;
		i++;
	}
	map_and_txt[i] = NULL;
	close(fd);
	return (map_and_txt);
}
