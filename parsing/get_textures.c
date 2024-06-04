/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:38:10 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 16:50:00 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	process_texture(t_game *game, t_curs *curs)
{
	if (ft_strncmp(&game->txts.txts[curs->i][curs->j], "NO ", 3) == 0)
		game->txts.imgs[0].img = get_img(game->txts.txts[curs->i] + curs->j + 3,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "SO ", 3) == 0)
		game->txts.imgs[1].img = get_img(game->txts.txts[curs->i] + curs->j + 3,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "WE ", 3) == 0)
		game->txts.imgs[2].img = get_img(game->txts.txts[curs->i] + curs->j + 3,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "EA ", 3) == 0)
		game->txts.imgs[3].img = get_img(game->txts.txts[curs->i] + curs->j + 3,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "C ", 2) == 0)
		game->txts.imgs[4].img = get_floor(game->txts.txts[curs->i] + 1, game,
				curs->i);
	else if (ft_strncmp(game->txts.txts[curs->i], "F ", 2) == 0)
		game->txts.imgs[5].img = get_floor(game->txts.txts[curs->i] + 1, game,
				curs->i);
	else
		process_texture2(game, curs);
}

void	process_texture2(t_game *game, t_curs *curs)
{
	int	i;

	i = 10;
	if (ft_strncmp(game->txts.txts[curs->i], "DD ", 2) == 0)
		game->txts.imgs[6].img = get_img(game->txts.txts[curs->i] + curs->j + 3,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "X ", 2) == 0)
		game->txts.imgs[7].img = get_img(game->txts.txts[curs->i] + curs->j + 2,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "XL ", 3) == 0)
		game->txts.imgs[8].img = get_img(game->txts.txts[curs->i] + curs->j + 3,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "XXL ", 4) == 0)
		game->txts.imgs[9].img = get_img(game->txts.txts[curs->i] + curs->j + 4,
				game);
	else if (ft_strncmp(game->txts.txts[curs->i], "L ", 2) == 0)
		game->txts.imgs[i].img = get_img(game->txts.txts[curs->i] + curs->j + 2,
				game);
	else
		err_exit("Error: Invalid texture", game);
}
