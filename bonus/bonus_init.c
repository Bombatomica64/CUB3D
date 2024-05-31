/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:02:11 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/31 17:47:40 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include <functions.h>

void	minimap_init(t_game *game)
{
	int	i;

	i = 0;
	game->bonus.height = (double)game->map_height * MINIMAP_SCALE;
	game->bonus.width = (double)game->map_width * MINIMAP_SCALE;
	game->bonus.minimap = ft_calloc(game->map_height + 1, sizeof(char *));
	while (i < game->map_height)
	{
		game->bonus.minimap[i] = ft_strdup(game->map[i]);
		i++;
	}
	printf("game->bonus.height: %d\n", game->bonus.height);
	printf("game->bonus.width: %d\n", game->bonus.width);
	printf("minimap\n");
	printf("game->bonus.minimap[y][x]: %d\n",
		game->bonus.minimap[(int)game->player.pos.y][(int)game->player.pos.x]);
	print_matrix((char **)game->bonus.minimap);
}

void	sprite_init(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	game->bonus.sprite.nb_sprites = 0;
	while (curs.i < game->map_height)
	{
		curs.j = 0;
		while (curs.j < game->map_width)
		{
			if (game->bonus.minimap[curs.i][curs.j] == 'X')
				game->bonus.sprite.nb_sprites++;
			curs.j++;
		}
		curs.i++;
	}
	game->bonus.sprite.pos = ft_calloc(game->bonus.sprite.nb_sprites,
			sizeof(t_pos));
	game->bonus.sprite.sprite_dist = ft_calloc(game->bonus.sprite.nb_sprites,
			sizeof(double));
	game->bonus.sprite.sprite_order = ft_calloc(game->bonus.sprite.nb_sprites,
			sizeof(int));
	curs.i = 0;
	while (curs.i < game->map_height)
	{
		curs.j = 0;
		while (curs.j < game->map_width)
		{
			if (game->bonus.minimap[curs.i][curs.j] == 'X')
			{
				game->bonus.sprite.pos[curs.k] = (t_pos){curs.j + 0.5, curs.i + 0.5};
				curs.k++;
			}
			curs.j++;
		}
		curs.i++;
	}
}

void	bonus_init(t_game *game)
{
	minimap_init(game);
	sprite_init(game);
}
