/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:33:08 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/17 10:55:20 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	parse_line(char *line, t_game *game)
{
	t_curs		curs;

	curs = (t_curs){0, 0, 0, 0};
	curs.i += skip_spaces2(line);
	if (line[curs.i] == '\0')
		return (free(line), 0);
	if (is_in_mtx(&line[curs.i], game->txts.txt_nm) == 1
		&& game->input.map_str == 0)
		game->txts.txts = add_to_matrix(ft_strtrimfree(game->txts.txts,
					"\n", &curs.j), line);
	else if (ft_isinset(line[curs.i], "01NSEW"))
	{
		game->map = add_to_matrix(ft_strtrimfree(game->txts.txts,
					"\n", &curs.j), line);
		game->input.map_str = 1;
	}
	else
		return (free(line), -1);
	free(line);
	return (0);
}

void	pad_map(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (game->map[curs.i])
	{
		if (ft_strlen(game->map[curs.i]) > curs.status)
			curs.status = ft_strlen(game->map[curs.i]);
		curs.i++;
	}
	while (game->map[curs.j])
	{
		if (ft_strlen(game->map[curs.j]) < curs.status)
			game->map[curs.j] = join_n_char(game->map[curs.j], ' ',
					curs.status - ft_strlen(game->map[curs.j]));
		curs.j++;
	}
}

void	split_map(t_game *game)
{
	int		size;
	int		i;
	char	*line;

	i = 0;
	size = ft_matrix_len(game->input.map_and_txt);
	while (i < size)
	{
		line = ft_strdup(game->input.map_and_txt[i]);
		if (parse_line(line, game) != -1)
			i++;
		else
			err("Failed to parse line");
	}
	pad_map(game);
}
