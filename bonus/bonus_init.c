/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:02:11 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 12:50:58 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	minimap_init(t_game *game)
{
	int	i;

	i = 0;
	game->bonus.height = (double)game->map_height * MINIMAP_SCALE;
	game->bonus.width = (double)game->map_width * MINIMAP_SCALE;
	game->bonus.minimap = ft_calloc(game->map_height + 1, sizeof(int *));
	while (i < game->map_height)
	{
		game->bonus.minimap[i] = (int *)ft_strdup(game->map[i]);
		i++;
	}
	printf("game->bonus.height: %d\n", game->bonus.height);
	printf("game->bonus.width: %d\n", game->bonus.width);
	printf("minimap\n");
	game->bonus.minimap[(int)game->player.pos.y][(int)game->player.pos.x] = 80;
	printf("game->bonus.minimap[(int)game->player.pos.y][(int)game->player.pos.x]: %d\n",
	game->bonus.minimap[(int)game->player.pos.y][(int)game->player.pos.x]);
	print_matrix((char **)game->bonus.minimap);
}

void	bonus_init(t_game *game)
{
	minimap_init(game);
}
