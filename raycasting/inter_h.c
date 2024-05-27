/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:24:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 18:36:21 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

// static double	calc_first_inter(t_game *game, double angle)
// {
// 	double	tan_angle;

// 	tan_angle = fast_tan(angle);
// 	game->ray.y_int = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
// 	if (angle > M_PI && angle < 2 * M_PI)
// 		game->ray.y_int += TILE_SIZE;
// 	game->ray.x_int = game->player.x
// 		+ (game->player.y - game->ray.y_int) / tan_angle;
// 	return (tan_angle);
// }

// static void	calculate_steps(t_game *game, double tan_angle,
// 	double *x_step, double *y_step)
// {
// 	*y_step = TILE_SIZE;
// 	if (nor_angle(game->ray.angle) > M_PI
// 		&& nor_angle(game->ray.angle) < 2 * M_PI)
// 		*y_step *= -1;
// 	*x_step = TILE_SIZE / tan_angle;
// 	if (nor_angle(game->ray.angle) > M_PI
// 		/ 2 && nor_angle(game->ray.angle) < 3 * M_PI / 2)
// 		*x_step *= -1;
// }

// static double	check_for_wall(t_game *game, double x_step, double y_step)
// {
// 	double	x;
// 	double	y;

// 	x = game->ray.x_int;
// 	y = game->ray.y_int;
// 	while (x >= 0 && x < game->map_width
// 		* TILE_SIZE)
// 	{
// 		if (is_wall(x, y, game) == 1)
// 		{
// 			game->ray.flag = 1;
// 			return (pow(game->player.x - x, 2) + pow(game->player.y - y, 2));
// 		}
// 		x += x_step;
// 		y += y_step;
// 	}
// 	game->ray.hor_x = x;
// 	game->ray.hor_y = y;
// 	return (INT_MAX);
// }

// int	check_inter(double angle, double *y, double *y_step, int flag)
// {
// 	if (flag == 1)
// 	{
// 		if (angle < M_PI && angle > 0)
// 		{
// 			*y += TILE_SIZE;
// 			return (-1);
// 		}
// 		*y_step *= -1;
// 	}
// 	else
// 	{
// 		if (angle < 3 * M_PI / 2 && angle > M_PI / 2)
// 		{
// 			*y += TILE_SIZE;
// 			return (-1);
// 		}
// 		*y_step *= -1;
// 	}
// 	return (1);
// }

// double	horizontal_inter(t_game *game)
// {
// 	double	x_step;
// 	double	y_step;
// 	double	h_y;
// 	double	h_x;

// 	if (game->ray.angle > 0 && game->ray.angle < M_PI)
// 	{
// 		y_step = TILE_SIZE;
// 		h_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
// 	}
// 	else
// 	{
// 		y_step = -TILE_SIZE;
// 		h_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE - 1;
// 	}
// 	x_step = TILE_SIZE / tan(game->ray.angle);
// 	if ((game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2)
// 		&& x_step > 0)
// 		x_step = -x_step;
// 	else if ((game->ray.angle <= M_PI_2 || game->ray.angle >= 3 * M_PI_2)
// 		&& x_step < 0)
// 		x_step = -x_step;
// 	h_x = game->player.x + (game->player.y - h_y)
// 		/ tan(game->ray.angle);
// 	while (is_wall(h_x, h_y, game))
// 	{
// 		h_x += x_step;
// 		h_y += y_step;
// 	}
// 	return (fabs((game->player.y - h_y) / cos(game->ray.angle)));
// }
