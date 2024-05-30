/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 12:53:07 by lmicheli         ###   ########.fr       */
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

// void	flood_map(char **map, int i, int j, t_game *game)
// {
// 	if (i <= 0 || j <= 0 || i >= (int)ft_matrix_len(map)
// 		|| j >= (int)ft_strlen(map[i]) || map[i][j] == ' ')
// 		err_exit("Error :\n Invalid map", game);
// 	if (map[i][j] == '1')
// 		return ;
// 	flood_map(map, i + 1, j, game);
// 	flood_map(map, i - 1, j, game);
// 	flood_map(map, i, j + 1, game);
// 	flood_map(map, i, j - 1, game);
// }

// int	check_forzeros(char **map)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == '0')
// 				return (-1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	check_closed_space(t_game *game, t_curs curs)
{
	if (curs.i == 0 || curs.j == 0
		|| curs.i == (int)ft_matrix_len(game->map)
		|| curs.j == (int)ft_strlen(game->map[curs.i]) - 1
		|| game->map[curs.i][curs.j + 1] == ' '
		|| game->map[curs.i][curs.j - 1] == ' '
		|| game->map[curs.i + 1][curs.j] == ' '
		|| game->map[curs.i - 1][curs.j] == ' ')
		err_exit("Error :\n Invalid map", game);
}

void	check_map(t_game *game)
{
	t_curs	curs;
	char	*line;

	curs = (t_curs){0, 0, ft_matrix_len(game->map) - 1, 0};
	while (curs.k >= 0)
	{
		line = ft_strtrim(game->map[curs.k], " \n");
		if (line[0] != '\0')
			curs.status = 1;
		if (curs.status == 1 && line[0] == '\0')
		{
			free(line);
			err_exit("Invalid map1", game);
		}
		free(line);
		curs.k--;
	}
	curs.k = 0;
	while (game->map[curs.i])
	{
		curs.j = 0;
		while (game->map[curs.i][curs.j])
		{
			if (ft_isinset(game->map[curs.i][curs.j], "NSEW"))
			{
				printf("cur.i = %d\ncur.j = %d\n", curs.i, curs.j);
				init_player(game, curs.i, curs.j);
				curs.k++;
			}
			curs.j++;
		}
		curs.i++;
	}
	if (curs.k != 1)
		err_exit("Invalid map2", game);
	while (game->map[curs.i])
	{
		curs.j = 0;
		while (game->map[curs.i][curs.j])
		{
			if (!ft_isinset(game->map[curs.i][curs.j], " 01NSEW"))
				err_exit("Invalid character in map", game);
			else if (ft_isinset(game->map[curs.i][curs.j], "0NSEW"))
				check_closed_space(game, curs);
			curs.j++;
		}
		curs.i++;
	}
	return ;
}
