/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 18:09:13 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	init_player_north_south(t_player *player)
{
	double	plane_length;
	double	fov_rad;

	fov_rad = FOV * M_PI / 180;
	plane_length = tan(fov_rad / 2);
	if (player->name == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -plane_length;
		player->plane.y = 0;
	}
	else if (player->name == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = plane_length;
		player->plane.y = 0;
	}
	else
		return ;
}

static void	init_player_east_west(t_player *player)
{
	double	plane_length;
	double	fov_rad;

	fov_rad = FOV * M_PI / 180;
	plane_length = tan(fov_rad / 2);
	if (player->name == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -plane_length;
	}
	else if (player->name == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = plane_length;
	}
	else
		return ;
}

void	init_player(t_game *game, int y, int x)
{
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	game->player.name = game->map[y][x];
	init_player_north_south(&game->player);
	init_player_east_west(&game->player);
}

	// printf("name: |%c|\n", game->player.name);
	// printf("player.x: %f\nplayer.y: %f\nplayer.angle:
	//  %f\n", game->player.pos.x,
	// 	game->player.pos.y, game->player.angle);
	// printf("player.dir.x: %f\nplayer.dir.y: %f\nplayer.plane.x:
	// 	%f\nplayer.plane.y: %f\n", game->player.dir.x, game->player.dir.y,
	// 	game->player.plane.x, game->player.plane.y);