/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 17:41:29 by lmicheli         ###   ########.fr       */
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
		err_exit("Error : Failed to open map file", game);
	while (get_next_line2(fd, &line) > 0)
		i++;
	free(line);
	i++;
	game->input.file_len = i;
	close(fd);
	if (game->input.file_len == 1)
		err_exit("Error: Empty map file", game);
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
		err_exit("Error: Failed to open map file", game);
	map_and_txt = malloc(sizeof(char *) * (game->input.file_len + 1));
	if (!map_and_txt)
		err_exit("Error: Failed to allocate map", game);
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

void	check_map(t_game *game)
{
	checksmh(game);
	check_and_init_player(game);
	if (BONUS == 0)
		check_chars(game, (t_curs){0, 0, 0, 0});
	else
		check_chars_bonus(game, (t_curs){0, 0, 0, 0});
}
