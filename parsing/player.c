/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/28 11:39:10 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	init_player_north_south(t_player *player)
{
	if (player->name == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -(double)SCREEN_HEIGHT / (double)SCREEN_WIDTH;
		player->plane.y = 0;
	}
	else if (player->name == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = (double)SCREEN_HEIGHT / (double)SCREEN_WIDTH;
		player->plane.y = 0;
	}
	else
		return ;
}

static void	init_player_east_west(t_player *player)
{
	if (player->name == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -(double)SCREEN_HEIGHT / (double)SCREEN_WIDTH;
	}
	else if (player->name == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = (double)SCREEN_HEIGHT / (double)SCREEN_WIDTH;
	}
	else
		return ;
}

void	init_player(t_game *game, int y, int x)
{
	game->player.x = x * TILE_SIZE + (TILE_SIZE / 2);
	game->player.y = y * TILE_SIZE + (TILE_SIZE / 2);
	game->player.name = game->map[y][x];
	init_player_north_south(&game->player);
	init_player_east_west(&game->player);
	printf("player.x: %f\nplayer.y: %f\nplayer.angle: %f\n", game->player.x, game->player.y, game->player.angle);
}
