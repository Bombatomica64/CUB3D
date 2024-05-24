/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/24 12:18:06 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	get_wall_dist(t_game *game)
{
	t_pos		steps;

	steps.x = TILE_SIZE / tan(game->ray.angle);
	printf("angle = %f\n", game->ray.angle);
	printf("tan = %f\n", tan(game->ray.angle));
	if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
	{
		steps.x = -steps.x;
		game->ray.next.x = (game->player.x / TILE_SIZE) * TILE_SIZE - 1;
	}
	else
		game->ray.next.x = (game->player.x / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
	steps.y = TILE_SIZE * tan(game->ray.angle);
	if (game->ray.angle < M_PI / 2 || game->ray.angle > 3 * M_PI / 2)
	{
		steps.y = -steps.y;
		game->ray.next.y = game->player.y - 1;
	}
	else
		game->ray.next.y = game->player.y + TILE_SIZE;
	printf("next.x = %f, next.y = %f\n", game->ray.next.x, game->ray.next.y);
	while (TRUE)
	{
		game->ray.next.x += steps.x;
		game->ray.next.y += steps.y;
		if (is_wall(game->ray.next.x, game->ray.next.y, game) )
			break ;
	}
	return (sqrt(pow(game->player.x - game->ray.next.x, 2)
			+ pow(game->player.y - game->ray.next.y, 2)));
}

void	cast_rays(t_game *game)
{
	double	increment;

	game->ray.i_ray = 0;
	increment = game->fov_rd / SCREEN_WIDTH;
	game->ray.angle = game->player.angle - (game->fov_rd / 2);
	while (game->ray.i_ray <= SCREEN_WIDTH)
	{
		game->ray.flag = 0;
		game->ray.angle = nor_angle(game->ray.angle);
		game->ray.dist = get_wall_dist(game);
		printf("ray %d: dist = %f\n", game->ray.i_ray, game->ray.dist);
		render_wall(game);
		game->ray.angle += increment;
		game->ray.i_ray++;
	}
	return ;
}

// double	get_wall_dist(t_game *game)
// {
// 	double	x_step;
// 	double	y_step;
// 	double	next_x;
// 	double	next_y;
// 	int		hit_side;

// 	if (game->ray.angle > 0 && game->ray.angle < M_PI)
// 	{
// 		y_step = TILE_SIZE;
// 		next_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
// 		hit_side = 0;
// 	}
// 	else
// 	{
// 		y_step = -TILE_SIZE;
// 		next_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE - 1;
// 		hit_side = 1;
// 	}
// 	x_step = TILE_SIZE / tan(game->ray.angle);
// 	if ((game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2)
// 		&& x_step > 0)
// 		x_step = -x_step;
// 	else if ((game->ray.angle <= M_PI_2 || game->ray.angle >= 3 * M_PI_2)
// 		&& x_step < 0)
// 		x_step = -x_step;
// 	next_x = game->player.x + (game->player.y - next_y)
// 		/ tan(game->ray.angle);
// 	while (is_wall(next_x, next_y, game))
// 	{
// 		next_x += x_step;
// 		next_y += y_step;
// 		if (next_x < 0 || next_x >= game->map_width * TILE_SIZE
// 			|| next_y < 0 || next_y >= game->map_height * TILE_SIZE)
// 			return (INFINITY);
// 		if (hit_side == 0 && (game->ray.angle > 0 && game->ray.angle < M_PI))
// 		{
// 			if (check_inter(game->ray.angle, &next_y, &y_step, 1))
// 			{
// 				hit_side = 1;
// 				x_step = TILE_SIZE / tan(game->ray.angle);
// 				if (game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2)
// 					x_step = -x_step;
// 				next_x = game->player.x
// 					+ (game->player.y - next_y) / tan(game->ray.angle);
// 			}
// 		}
// 		else if (hit_side == 0
// 			&& (game->ray.angle < 0 || game->ray.angle > M_PI))
// 		{
// 			if (check_inter(game->ray.angle, &next_y, &y_step, 0))
// 			{
// 				hit_side = 1;
// 				x_step = TILE_SIZE / tan(game->ray.angle);
// 				if (game->ray.angle <= M_PI_2 || game->ray.angle >= 3 * M_PI_2)
// 					x_step = -x_step;
// 				next_x = game->player.x + (game->player.y - next_y)
// 					/ tan(game->ray.angle);
// 			}
// 		}
// 		if (hit_side == 1
// 			&& (game->ray.angle < M_PI_2 || game->ray.angle > 3 * M_PI_2))
// 		{
// 			if (check_inter(game->ray.angle, &next_x, &x_step, 0))
// 			{
// 				hit_side = 0;
// 				y_step = TILE_SIZE * tan(game->ray.angle);
// 				if (game->ray.angle > M_PI && game->ray.angle < 2 * M_PI)
// 					y_step = -y_step;
// 				next_y = game->player.y + (next_x - game->player.x)
// 					* tan(game->ray.angle);
// 			}
// 		}
// 		else if (hit_side == 1
// 			&& (game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2))
// 		{
// 			if (check_inter(game->ray.angle, &next_x, &x_step, 1))
// 			{
// 				hit_side = 0;
// 				y_step = TILE_SIZE * tan(game->ray.angle);
// 				if (game->ray.angle < M_PI && game->ray.angle > 0)
// 					y_step = -y_step;
// 				next_y = game->player.y + (next_x - game->player.x)
// 					* tan(game->ray.angle);
// 			}
// 		}
// 	}
// 	return (sqrt(pow(game->player.x - next_x, 2)
// 			+ pow(game->player.y - next_y, 2)));
// }