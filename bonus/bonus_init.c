/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:02:11 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 17:48:23 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	minimap_init(t_game *game)
{
	int	i;

	i = 0;
	game->bonus.height = (double)game->map_height * MINIMAP_SCALE;
	// if (game->bonus.height > SCREEN_HEIGHT / 4)
	// 	game->bonus.height = SCREEN_HEIGHT / 4;
	game->bonus.width = (double)game->map_width * MINIMAP_SCALE;
	// if (game->bonus.width > SCREEN_WIDTH / 4)
	// 	game->bonus.width = SCREEN_WIDTH / 4;
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

void	bonus_init(t_game *game)
{
	minimap_init(game);
}
