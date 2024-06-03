/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 18:43:41 by mruggier         ###   ########.fr       */
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

t_bool	ray_hit(t_game *game)
{
	char	map_value;

	map_value = game->map[(int)game->ray.map.y][(int)game->ray.map.x];
	if (map_value == '1' || map_value == 'D')
	{
		game->bonus.doors.wall_hit = map_value;
		if (BONUS && map_value == '1' && game->bonus.doors.door_open == 1)
		{
			game->bonus.doors.wallx = (int)game->ray.map.x;
			game->bonus.doors.wally = (int)game->ray.map.y;
		}
		if (BONUS && game->map[(int)game->player.pos.y][(int)game->player.pos.x]
			== 'L')
			game->bonus.doors.insidedoor = true;
		return (true);
	}
	if (map_value == 'L')
	{
		game->bonus.doors.door_open = 1;
		game->bonus.doors.doorx = (int)game->ray.map.x;
		game->bonus.doors.doory = (int)game->ray.map.y;
	}
	return (false);
}

static void	dda_exec(t_game *game)
{
	bool	hit;

	hit = false;
	if (BONUS)
		game->bonus.doors = (t_door){0, 0, 0, 0, 0, 0, false};
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
		hit = ray_hit(game);
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
		game->ray.wall_x = game->player.pos.y + game->ray.dist
			* game->ray.dir.y;
	else
		game->ray.wall_x = game->player.pos.x + game->ray.dist
			* game->ray.dir.x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	if (BONUS)
		game->bonus.sprite.zbuffer[x] = game->ray.dist;
}

int	cast_rays(t_game *game)
{
	int		x;
	long	time;

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
	return (0);
}
