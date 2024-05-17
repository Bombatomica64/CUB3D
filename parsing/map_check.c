/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:14:51 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/17 14:49:15 by lmicheli         ###   ########.fr       */
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

void	flood_map(char **map, int i, int j)
{
	if (i <= 0 || j <= 0 || i >= ft_matrix_len(map)
		|| j >= ft_strlen(map[i]) || map[i][j] == ' ')
		err("Invalid map");
	if (map[i][j] == '1')
		return ;
	map[i][j] = 'F';
	flood_map(map, i + 1, j);
	flood_map(map, i - 1, j);
	flood_map(map, i, j + 1);
	flood_map(map, i, j - 1);
}

int	check_forzeros(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	check_closed_space(t_game *game, t_curs curs)
{
	char	**map;

	map = matrixdup(game->map);
	flood_map(map, curs.i, curs.j);
	if (check_forzeros(map) == -1)
		err_exit("\n", game);
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
