/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_v.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:52 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/22 17:03:53 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

// static double	calc_first_inter(t_game *game, double angle)
// {
// 	double	tan_angle;

// 	tan_angle = fast_tan(angle);
// 	game->ray.x_int = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
// 	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
// 		game->ray.x_int += TILE_SIZE;
// 	game->ray.y_int = game->player.y
// 		+ (game->player.x - game->ray.x_int) * tan_angle;
// 	return (tan_angle);
// }

// static void	calculate_steps(t_game *game, double tan_angle,
// 	double *x_step, double *y_step)
// {
// 	*x_step = TILE_SIZE;
// 	if (nor_angle(game->ray.angle) > M_PI / 2
// 		&& nor_angle(game->ray.angle) < 3 * M_PI / 2)
// 		*x_step *= -1;
// 	*y_step = TILE_SIZE * tan_angle;
// 	if (nor_angle(game->ray.angle) > M_PI
// 		&& nor_angle(game->ray.angle) < 2 * M_PI)
// 		*y_step *= -1;
// 	fprintf(stderr, "x_step: %f, y_step: %f\n", *x_step, *y_step);
// }

// static double	check_for_wall(t_game *game, double x_step, double y_step)
// {
// 	double	x;
// 	double	y;

// 	x = game->ray.x_int;
// 	y = game->ray.y_int;
// 	fprintf(stderr, "x: %f, y: %f\n", x, y);
// 	while (y >= 0 && y < game->map_height * TILE_SIZE)
// 	{
// 		if (is_wall(x, y, game) == 1)
// 		{
// 			game->ray.flag = 1;
// 			return (pow(game->player.x - x, 2) + pow(game->player.y - y, 2));
// 		}
// 		x += x_step;
// 		y += y_step;
// 	}
// 	game->ray.ver_x = x;
// 	game->ray.ver_y = y;
// 	return (INT_MAX);
// }

double	vertical_inter(t_game *game)
{
	double	x_step;
	double	y_step;
	double	v_x;
	double	v_y;
	int		pixel;

	if (game->ray.angle < M_PI / 2 || game->ray.angle > 3 * M_PI / 2)
	{
		x_step = TILE_SIZE;
		v_x = floor(game->player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		pixel = 0;
	}
	else
	{
		x_step = -TILE_SIZE;
		v_x = floor(game->player.x / TILE_SIZE) * TILE_SIZE - 1;
		pixel = 1;
	}
	y_step = TILE_SIZE * tan(game->ray.angle);
	if ((game->ray.angle > M_PI && game->ray.angle < 2 * M_PI && y_step > 0)
		|| (game->ray.angle < M_PI && y_step < 0))
	{
		y_step = -y_step;
	}
	v_y = game->player.y + (v_x - game->player.x) * tan(game->ray.angle);
	while (is_wall(v_x, v_y, game))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray.ver_x = v_x;
	game->ray.ver_y = v_y;
	return (fabs((game->player.x - v_x) / cos(game->ray.angle)));
}
