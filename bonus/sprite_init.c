/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:54:51 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 12:57:20 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	sprite_nb(t_game *game)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->bonus.minimap[i][j] == 'X')
				nb++;
			j++;
		}
		i++;
	}
	game->bonus.sprite.nb_sprites = nb;
	game->bonus.sprite.pos = ft_calloc(game->bonus.sprite.nb_sprites + 1,
			sizeof(t_pos));
	game->bonus.sprite.sprite_dist = ft_calloc(game->bonus.sprite.nb_sprites
			+ 1, sizeof(double));
	game->bonus.sprite.sprite_order = ft_calloc(game->bonus.sprite.nb_sprites
			+ 1, sizeof(int));
}

void	sprite_init(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	game->bonus.sprite.nb_sprites = 0;
	sprite_nb(game);
	curs.i = 0;
	while (curs.i < game->map_height)
	{
		curs.j = 0;
		while (curs.j < game->map_width)
		{
			if (game->bonus.minimap[curs.i][curs.j] == 'X')
			{
				game->bonus.sprite.pos[curs.k] = (t_pos){curs.j + 0.5, curs.i
					+ 0.5, 0};
				curs.k++;
			}
			curs.j++;
		}
		curs.i++;
	}
}

void	rand_init(t_game *game)
{
	srand(time(NULL));
	game->bonus.sprite.text_nb = rand() % 2 + 6;
	game->bonus.frame = 0;
	game->bonus.time = get_time();
	game->bonus.frame_time = get_time();
}
