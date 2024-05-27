/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:05:29 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 17:31:31 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	init_player_north_south(t_player *player)
{
	if (player->name == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
	else if (player->name == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
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
		player->plane.y = -0.66;
	}
	else if (player->name == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else
		return ;
}

void	init_player(t_game *game, int x, int y)
{
	game->player.x = x * TILE_SIZE + (TILE_SIZE / 2);
	game->player.y = y * TILE_SIZE + (TILE_SIZE / 2);
	game->player.name = game->map[y][x];
	init_player_north_south(&game->player);
	init_player_east_west(&game->player);
	game->player.dist_proj = (SCREEN_WIDTH / 2) / tan(game->fov_rd / 2);
	printf("player.x: %f\nplayer.y: %f\nplayer.angle: %f\nplayer.dist_proj: %f\n", game->player.x, game->player.y, game->player.angle, game->player.dist_proj);
}
