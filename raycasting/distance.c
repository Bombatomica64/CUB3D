/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 10:20:54 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	reycast_init(int x, t_game *game)
{
	game->ray.camera_x = 2 * x / SCREEN_WIDTH - 1;
	game->ray.dir.x = game->player.dir.x
		+ game->player.plane.x * game->ray.camera_x;
	game->ray.dir.y = game->player.dir.y
		+ game->player.plane.y * game->ray.camera_x;
	game->ray.map.x = (int)game->player.pos.x;
	game->ray.map.y = (int)game->player.pos.y;
	game->ray.delta_dist.x = fabs(1.0 / game->ray.dir.x);
	game->ray.delta_dist.y = fabs(1.0 / game->ray.dir.y);
}

/*
- We are doing the initial set up for the dda
- dda algorithm will jump one square in each loop eiter in a x or y dir
- ray->side_dist.x or y = distance from the ray start pos to the
	next x or y pos
- if x or y < 0 go the next x or y to the left
- if x or y > 0 go the next x or y to the right
*/

static void	dda_init(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step.x = -1;
		game->ray.side_dist.x = (game->player.pos.x - game->ray.map.x)
			* game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step.x = 1;
		game->ray.side_dist.x = (game->ray.map.x + 1.0 - game->player.pos.x)
			* game->ray.delta_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step.y = -1;
		game->ray.side_dist.y = (game->player.pos.y - game->ray.map.y)
			* game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step.y = 1;
		game->ray.side_dist.y = (game->ray.map.y + 1.0 - game->player.pos.y)
			* game->ray.delta_dist.y;
	}
}

/*
- We implement the DDA algorithm -> the loop will increment 1 square 
-   until we hit a wall
- If the sidedistx < sidedisty, x is the closest point from the ray
*/

static void	dda_exec(t_game *game)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta_dist.x;
			game->ray.map.x += game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta_dist.y;
			game->ray.map.y += game->ray.step.y;
			game->ray.side = 1;
		}
		if (game->ray.map.y < 0.25 || game->ray.map.x < 0.25
			|| game->ray.map.y > game->map_height - 0.25
			|| game->ray.map.x > game->map_width - 1.25)
			break ;
		else if (game->map[(int)game->ray.map.y][(int)game->ray.map.x] == '1')
		{
			hit = true;
			if (BONUS)
				game->bonus.wall_hit = '1';
		}
		else if (game->map[(int)game->ray.map.y][(int)game->ray.map.x] == 'D')
		{
			hit = true;
			game->bonus.wall_hit = 'D';
			game->bonus.door = 1;
		}
		// else if (game->map[(int)game->ray.map.y][(int)game->ray.map.x] == 'S')
		// 	sesso;
	}
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
		game->ray.wall_x = game->player.pos.y
			+ game->ray.dist * game->ray.dir.y;
	else
		game->ray.wall_x = game->player.pos.x
			+ game->ray.dist * game->ray.dir.x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	if (BONUS)
		game->bonus.sprite.zbuffer[x] = game->ray.dist;
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
	if (BONUS)
		sprite_calc(game);
	return (0);
}
