/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 17:37:11 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	nor_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

// t_img	get_texture(t_game *game)
// {
// 	game->ray.angle = nor_angle(game->ray.angle);
// 	if (game->ray.flag == 0)
// 	{
// 		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
// 			return (game->txts.imgs[3]);
// 		else
// 			return (game->txts.imgs[2]);
// 	}
// 	else
// 	{
// 		if (game->ray.angle > 0 && game->ray.angle < M_PI)
// 			return (game->txts.imgs[1]);
// 		else
// 			return (game->txts.imgs[0]);
// 	}
// }

// int	get_texture_id(t_game *game)
// {
// 	game->ray.angle = nor_angle(game->ray.angle);
// 	if (game->ray.flag == 0)
// 	{
// 		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
// 			return (3);
// 		else
// 			return (2);
// 	}
// 	else
// 	{
// 		if (game->ray.angle > 0 && game->ray.angle < M_PI)
// 			return (1);
// 		else
// 			return (0);
// 	}
// }

int	unit_circle(double angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (1);
	}
	return (0);
}
