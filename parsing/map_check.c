/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:14:51 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/17 11:08:18 by lmicheli         ###   ########.fr       */
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

void	flood_map(t_game *game, int i, int j)
{
	if (i < 0 || j < 0 || i >= ft_matrix_len(game->map)
		|| j >= ft_strlen(game->map[i]) || game->map[i][j] == '1' ||
		game->map[i][j] == ' ')
		err_exit("Invalid map", game);
	flood_map(game, i + 1, j);
	flood_map(game, i - 1, j);
	flood_map(game, i, j + 1);
	flood_map(game, i, j - 1);
}

void	check_closed_space(t_game *game, t_curs curs)
{
	flood_map(game, curs.i, curs.j);
}

void	check_map(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (game->map[curs.i])
	{
		curs.j = 0;
		while (game->map[curs.i][curs.j])
		{
			if (!ft_isinset(game->map[curs.i][curs.j], " 012NSEW"))
				err_exit("Invalid character in map", game);
			else if (game->map[curs.i][curs.j] == '0')
				check_closed_space(game, curs);
			curs.j++;
		}
		curs.i++;
	}
	return ;
}
