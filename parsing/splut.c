/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 12:30:47 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	parse_line(char *line, t_game *game)
{
	t_curs		curs;
	char *tmp;

	curs = (t_curs){0, 0, 0, 0};
	curs.i += skip_spaces2(line);
	if (line[curs.i] == '\0')
		return (free(line), 0);
	if (is_in_mtx(&line[curs.i], game->txts.txt_nm) == 1
		&& game->input.map_str == 0)
	{
		tmp = ft_strtrimfree(line, "\n", &curs.j);
		game->txts.txts = add_to_matrix(game->txts.txts, tmp);
		if (tmp != NULL)
			free(tmp);
	}
	else if (ft_isinset(line[curs.i], "01NSEW"))
	{
		tmp = ft_strtrimfree(line, "\n", &curs.j);
		game->map = add_to_matrix(game->map, tmp);
		if (tmp != NULL)
			free(tmp);
		game->input.map_str = 1;
	}
	else
		return (free(line), -1);
	return (0);
}

void	pad_map(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (game->map[curs.i])
	{
		if ((int)ft_strlen(game->map[curs.i]) > curs.status)
			curs.status = ft_strlen(game->map[curs.i]);
		curs.i++;
	}
	game->map_width = curs.status;
	while (game->map[curs.j])
	{
		if ((int)ft_strlen(game->map[curs.j]) < curs.status)
			game->map[curs.j] = join_n_char(game->map[curs.j], ' ',
					curs.status - ft_strlen(game->map[curs.j]));
		curs.j++;
	}
	game->map_height = ft_matrix_len(game->map);
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
			err_exit("Error: invalid input", game);
	}
	pad_map(game);
}
