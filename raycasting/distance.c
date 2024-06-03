/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 00:21:02 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	reycast_init(int x, t_game *game)
{
	game->ray.camera_x = 2 * x / SCREEN_WIDTH - 1;
	game->ray.dir.x = game->player.dir.x + game->player.plane.x
		* game->ray.camera_x;
	game->ray.dir.y = game->player.dir.y + game->player.plane.y
		* game->ray.camera_x;
	game->ray.map.x = (int)game->player.pos.x;
	game->ray.map.y = (int)game->player.pos.y;
	game->ray.delta_dist.x = fabs(1.0 / game->ray.dir.x);
	game->ray.delta_dist.y = fabs(1.0 / game->ray.dir.y);
}

static void	line_calc(t_game *game, int x)
{
	if (game->ray.side == 0)
		game->ray.dist = (game->ray.side_dist.x - game->ray.delta_dist.x);
	else
		game->ray.dist = (game->ray.side_dist.y - game->ray.delta_dist.y);
	game->ray.line_len = (SCREEN_HEIGHT / game->ray.dist);
	game->ray.drw_start = -(game->ray.line_len) / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.drw_start < 0)
		game->ray.drw_start = 0;
	game->ray.drw_end = game->ray.line_len / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.drw_end >= SCREEN_HEIGHT)
		game->ray.drw_end = SCREEN_HEIGHT - 1;
	if (game->ray.side == 0)
		game->ray.wall_x = game->player.pos.y + game->ray.dist
			* game->ray.dir.y;
	else
		game->ray.wall_x = game->player.pos.x + game->ray.dist
			* game->ray.dir.x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	if (BONUS)
		game->bonus.sprite.zbuffer[x] = game->ray.dist;
}

void	sprite_animation(t_game *game)
{
	long	time;

	if (BONUS)
	{
		if (game->bonus.sprite.nb_sprites > 0)
			sprite_calc(game);
		time = get_time();
		if (time - game->bonus.time > 300)
		{
			game->bonus.sprite.text_nb = game->bonus.sprite.text_nb + 1;
			game->bonus.time = time;
		}
		if (game->bonus.sprite.text_nb > 9)
			game->bonus.sprite.text_nb = 7;
	}
}

int	cast_rays(t_game *game)
{
	int		x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		reycast_init(x, game);
		dda_init(game);
		dda_exec(game);
		line_calc(game, x);
		pixels_update(game, x);
		x++;
	}
	sprite_animation(game);
	return (0);
}
