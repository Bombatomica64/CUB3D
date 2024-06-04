/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:05:31 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 18:13:26 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	check_closed_space(t_game *game, t_curs curs)
{
	if (curs.i == 0 || curs.j == 0 || curs.i == (int)ft_matrix_len(game->map)
		|| curs.j == (int)ft_strlen(game->map[curs.i]) - 1
		|| game->map[curs.i][curs.j + 1] == ' ' || game->map[curs.i][curs.j
		- 1] == ' ' || game->map[curs.i + 1][curs.j] == ' ' || game->map[curs.i
		- 1][curs.j] == ' ')
		err_exit("Error :\n Invalid map", game);
}

void	checksmh(t_game *game)
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
			err_exit("Error: Invalid map", game);
		}
		free(line);
		curs.k--;
	}
}

void	check_chars_bonus(t_game *game, t_curs curs)
{
	while (game->map[curs.i])
	{
		curs.j = 0;
		while (game->map[curs.i][curs.j])
		{
			if (!ft_isinset(game->map[curs.i][curs.j], " X01NSEWDL"))
				err_exit("Error :\n Invalid character in map", game);
			else if (ft_isinset(game->map[curs.i][curs.j], "X0NSEWDL"))
				check_closed_space(game, curs);
			curs.j++;
		}
		curs.i++;
	}
}

void	check_chars(t_game *game, t_curs curs)
{
	while (game->map[curs.i])
	{
		curs.j = 0;
		while (game->map[curs.i][curs.j])
		{
			if (!ft_isinset(game->map[curs.i][curs.j], " 01NSEW"))
				err_exit("Error :\n Invalid character in map", game);
			else if (ft_isinset(game->map[curs.i][curs.j], "0NSEW"))
				check_closed_space(game, curs);
			curs.j++;
		}
		curs.i++;
	}
}

void	check_and_init_player(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (game->map[curs.i])
	{
		curs.j = 0;
		while (game->map[curs.i][curs.j])
		{
			if (ft_isinset(game->map[curs.i][curs.j], "NSEW"))
			{
				init_player(game, curs.i, curs.j);
				game->map[curs.i][curs.j] = '0';
				curs.k++;
			}
			curs.j++;
		}
		curs.i++;
	}
	if (curs.k > 1)
		err_exit("Error: too many players", game);
	else if (curs.k == 0)
		err_exit("Error: no player", game);
}
