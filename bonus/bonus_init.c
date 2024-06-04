/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:02:11 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 12:55:30 by lmicheli         ###   ########.fr       */
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

void	porte_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'D' || game->map[i][j] == 'L')
			{
				game->bonus.door = 1;
				if (!((game->map[i][j - 1] == '1' && game->map[i][j + 1] == '1')
						|| (game->map[i - 1][j] == '1' && game->map[i
							+ 1][j] == '1')))
					err_exit("Error: door between opposite walls", game);
			}
			j++;
		}
		i++;
	}
}

void	bonus_check(t_game *game)
{
	if (game->bonus.door > 0)
	{
		if (game->txts.imgs[6].img.image == NULL)
			err_exit("Error: missing door texture", game);
		if (game->txts.imgs[6].img.width != TILE_SIZE
			|| game->txts.imgs[6].img.height != TILE_SIZE)
			err_exit("Error: door texture must be the correct size", game);
	}
	if (game->bonus.sprite.nb_sprites > 0)
	{
		if (!game->txts.imgs[7].img.image || !game->txts.imgs[8].img.image
			|| !game->txts.imgs[9].img.image)
			err_exit("Error: missing sprite texture", game);
		if (game->txts.imgs[7].img.width != TILE_SIZE
			|| game->txts.imgs[7].img.height != TILE_SIZE)
			err_exit("Error: sprite texture must be the correct size", game);
		if (game->txts.imgs[8].img.width != TILE_SIZE
			|| game->txts.imgs[8].img.height != TILE_SIZE)
			err_exit("Error: sprite texture must be the correct size", game);
		if (game->txts.imgs[9].img.width != TILE_SIZE
			|| game->txts.imgs[9].img.height != TILE_SIZE)
			err_exit("Error: sprite texture must be the correct size", game);
	}
}

void	bonus_init(t_game *game)
{
	porte_check(game);
	minimap_init(game);
	sprite_init(game);
	rand_init(game);
	bonus_check(game);
}
